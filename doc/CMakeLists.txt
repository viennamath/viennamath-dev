if(BUILD_DOXYGEN_DOCS)
   configure_file(Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
   add_custom_command(OUTPUT
      ${CMAKE_CURRENT_BINARY_DIR}/doxygen/html/index.html
      COMMAND ${DOXYGEN_EXECUTABLE}
      DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      VERBATIM)
   # Runs only once
   add_custom_target(apidoc-all ALL
      DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/doxygen/html/index.html)
   # For manual updates
   add_custom_target(apidoc
      COMMAND ${DOXYGEN_EXECUTABLE}
      DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      VERBATIM)
endif()

if(BUILD_MANUAL)
   set(MANUAL_SRCS
      manual/additional.tex
      manual/basic-types.tex
      manual/benchmarks.tex
      manual/changelogs.tex
      manual/contributors.tex
      manual/cover.tex
      manual/design-decisions.tex
      manual/expressions.tex
      manual/figures/logo_asc.eps
      manual/figures/logo_px200.eps
      manual/figures/note.eps
      manual/figures/tip.eps
      manual/figures/TU_Signet_CMYK.eps
      manual/IEEEtran_v1.13.bst
      manual/installation.tex
      manual/internals.tex
      manual/introduction.tex
      manual/keywords.tex
      manual/license.tex
      manual/manipulation.tex
      manual/setup.tex
      manual/viennamath.bib
      manual/viennamath.tex)

   set(MANUAL_OBJS
      "${CMAKE_CURRENT_BINARY_DIR}/viennamath.pdf"
      "${CMAKE_CURRENT_BINARY_DIR}/manual/viennamath.bbl"
      "${CMAKE_CURRENT_BINARY_DIR}/manual/viennamath.blg"
      "${CMAKE_CURRENT_BINARY_DIR}/manual/viennamath.dvi"
      "${CMAKE_CURRENT_BINARY_DIR}/manual/viennamath.idx"
      "${CMAKE_CURRENT_BINARY_DIR}/manual/viennamath.log"
      "${CMAKE_CURRENT_BINARY_DIR}/manual/viennamath.out"
      "${CMAKE_CURRENT_BINARY_DIR}/manual/viennamath.ps"
      "${CMAKE_CURRENT_BINARY_DIR}/manual/viennamath.toc")
   foreach(f IN LISTS MANUAL_SRCS)
      configure_file(${f} ${CMAKE_CURRENT_BINARY_DIR}/${f} COPYONLY)
      if(f MATCHES "(.*)\\.tex$")
         list(APPEND MANUAL_OBJS
            "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_MATCH_1}.aux")
      endif()
   endforeach()

   add_custom_command(OUTPUT ${MANUAL_OBJS}
      COMMAND ${LATEX_COMPILER} viennamath.tex
      COMMAND ${LATEX_COMPILER} viennamath.tex
      COMMAND ${BIBTEX_COMPILER} viennamath
      COMMAND ${LATEX_COMPILER} viennamath.tex
      COMMAND ${BIBTEX_COMPILER} viennamath
      COMMAND ${LATEX_COMPILER} viennamath.tex
      COMMAND ${DVIPS_CONVERTER} -Ppdf -G0 -ta4 viennamath.dvi
      COMMAND ${PS2PDF_CONVERTER} -dPDFSETTINGS=/prepress
         -dCompatibilityLevel=1.3 -dMAxSubsetPct=100 -dSubsetFonts=true
         -dEmbedAllFonts=true -sPAPERSIZE=a4 -dAutoRotatePages=/None
         -dOptimize=true viennamath.ps ../viennamath.pdf
      DEPENDS ${MANUAL_SRCS}
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/manual
      COMMENT "Generating manual viennamath.pdf"
      VERBATIM)

   add_custom_target(manual ALL
      DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/viennamath.pdf")
endif()
