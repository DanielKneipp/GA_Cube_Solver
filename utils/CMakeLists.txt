project(utils)

install(DIRECTORY DESTINATION ${CMAKE_INSTALL_PREFIX}/results)

install(FILES gen_configs.py DESTINATION ${CMAKE_INSTALL_PREFIX}/utils)
install(FILES proc_batch.py DESTINATION ${CMAKE_INSTALL_PREFIX}/utils)
install(FILES solution_converter.py DESTINATION ${CMAKE_INSTALL_PREFIX}/utils)
install(FILES get_overall_result.py DESTINATION ${CMAKE_INSTALL_PREFIX}/utils)
install(FILES overall_to_latex.py DESTINATION ${CMAKE_INSTALL_PREFIX}/utils)
