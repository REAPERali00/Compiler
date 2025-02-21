#include "Reader.h"
#include <check.h>
#include <stdlib.h>

#define TEST_SIZE 10
#define TEST_INCREMENT 5
#define TEST_MODE MODE_ADDIT

START_TEST(test_readerCreate) {
  ReaderPointer reader = readerCreate(TEST_SIZE, TEST_INCREMENT, TEST_MODE);
  ck_assert_ptr_nonnull(reader);
  ck_assert_int_eq(reader->size, TEST_SIZE);
  ck_assert_int_eq(reader->increment, TEST_INCREMENT);
  ck_assert_int_eq(reader->mode, TEST_MODE);
  readerFree(reader);
}
END_TEST

START_TEST(test_readerAddChar) {
  ReaderPointer reader = readerCreate(TEST_SIZE, TEST_INCREMENT, TEST_MODE);
  ck_assert_ptr_nonnull(reader);

  ck_assert_ptr_nonnull(readerAddChar(reader, 'A'));
  ck_assert_int_eq(reader->content[0], 'A');
  ck_assert_int_eq(reader->position.write, 1);

  readerFree(reader);
}
END_TEST

START_TEST(test_readerClear) {
  ReaderPointer reader = readerCreate(TEST_SIZE, TEST_INCREMENT, TEST_MODE);
  ck_assert_ptr_nonnull(reader);

  readerAddChar(reader, 'X');
  ck_assert_int_eq(reader->position.write, 1);

  ck_assert(readerClear(reader));
  ck_assert_int_eq(reader->position.write, 0);
  ck_assert_int_eq(reader->position.read, 0);

  readerFree(reader);
}
END_TEST

START_TEST(test_readerIsEmpty) {
  ReaderPointer reader = readerCreate(TEST_SIZE, TEST_INCREMENT, TEST_MODE);
  ck_assert_ptr_nonnull(reader);

  ck_assert(readerIsEmpty(reader));
  readerAddChar(reader, 'X');
  ck_assert(!readerIsEmpty(reader));

  readerFree(reader);
}
END_TEST

START_TEST(test_readerIsFull) {
  ReaderPointer reader = readerCreate(1, TEST_INCREMENT, MODE_FIXED);
  ck_assert_ptr_nonnull(reader);

  readerAddChar(reader, 'A');
  ck_assert(readerIsFull(reader));

  readerFree(reader);
}
END_TEST

START_TEST(test_readerSetMark) {
  ReaderPointer reader = readerCreate(TEST_SIZE, TEST_INCREMENT, TEST_MODE);
  ck_assert_ptr_nonnull(reader);

  ck_assert(readerSetMark(reader, 3));
  ck_assert_int_eq(reader->position.mark, 3);

  readerFree(reader);
}
END_TEST

START_TEST(test_readerGetChar) {
  ReaderPointer reader = readerCreate(TEST_SIZE, TEST_INCREMENT, TEST_MODE);
  ck_assert_ptr_nonnull(reader);

  readerAddChar(reader, 'B');
  readerAddChar(reader, 'C');

  ck_assert_int_eq(readerGetChar(reader), 'B');
  ck_assert_int_eq(readerGetChar(reader), 'C');

  readerFree(reader);
}
END_TEST

START_TEST(test_readerGetSize) {
  ReaderPointer reader = readerCreate(TEST_SIZE, TEST_INCREMENT, TEST_MODE);
  ck_assert_ptr_nonnull(reader);

  ck_assert_int_eq(readerGetSize(reader), TEST_SIZE);

  readerFree(reader);
}
END_TEST

Suite *reader_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Reader");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_readerCreate);
  tcase_add_test(tc_core, test_readerAddChar);
  tcase_add_test(tc_core, test_readerClear);
  tcase_add_test(tc_core, test_readerIsEmpty);
  tcase_add_test(tc_core, test_readerIsFull);
  tcase_add_test(tc_core, test_readerSetMark);
  tcase_add_test(tc_core, test_readerGetChar);
  tcase_add_test(tc_core, test_readerGetSize);

  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = reader_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
