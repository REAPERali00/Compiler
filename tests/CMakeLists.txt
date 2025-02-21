# Enable CTest for unit testing
enable_testing()

# Add test for Reader
add_executable(test_reader reader_tests.c)
target_link_libraries(test_reader PRIVATE reader check)
add_test(NAME ReaderTests COMMAND test_reader)

# # Add test for Scanner
# add_executable(test_scanner scanner_tests.c)
# target_link_libraries(test_scanner PRIVATE scanner check)
# add_test(NAME ScannerTests COMMAND test_scanner)
#
# # Add test for Parser
# add_executable(test_parser parser_tests.c)
# target_link_libraries(test_parser PRIVATE parser check)
# add_test(NAME ParserTests COMMAND test_parser)
#
