#include <UnitTest++/UnitTest++.h>
#include "modAlphaCipher.h"
#include <iostream>
#include <locale>
#include <codecvt>

using namespace std;
SUITE(KeyTest)
{

    TEST(LargeLetters) {
        modAlphaCipher test(L"КЛЮЧ");
        CHECK(true);
    }
    TEST(LargeAndSmallLetters) {
        modAlphaCipher test(L"ПРИВЕТмир");
        CHECK(true);
    }
    TEST(EmptyKey) {
        CHECK_THROW(modAlphaCipher test(L""), cipher_error);
    }
    TEST(Key_with_a_space) {
        CHECK_THROW(modAlphaCipher test(L"ПРИВЕТ МИР"), cipher_error);
    }
    TEST(Key_with_invalid_characters_number) {
        CHECK_THROW(modAlphaCipher test(L"12345"), cipher_error);
    }
    TEST(Key_with_invalid_characters_special_character) {
        CHECK_THROW(modAlphaCipher test(L"А?А?А?А?А?"), cipher_error);
    }
}

struct KeyAB_fixture {
    modAlphaCipher * pointer;
    KeyAB_fixture()
    {
        pointer = new modAlphaCipher(L"КЛЮЧ");
    }
    ~KeyAB_fixture()
    {
        delete pointer;
    }
};

SUITE(EncryptTest)
{
    TEST_FIXTURE(KeyAB_fixture, LargeLetters) {
        wstring open_text = L"ПРОСТОТЕКСТ";
        wstring result_correct = L"ЪЬМИЭЪРЬХЭР";
        CHECK_EQUAL(true, result_correct == pointer->encrypt(open_text));
    }
    TEST_FIXTURE(KeyAB_fixture, SmallLetters) {
        wstring open_text = L"ПростоТекст";
        wstring result_correct = L"ЪЛЮЧКЛКЧКЛЮ";
        CHECK_EQUAL(true, result_correct == pointer->encrypt(open_text));
    }
    TEST_FIXTURE(KeyAB_fixture,NumberInText ) {
        wstring open_text = L"12345";
        CHECK_THROW(pointer->encrypt(open_text),cipher_error);
    }
    TEST_FIXTURE(KeyAB_fixture,TextWithSpecialSymbol) {
        wstring open_text = L"А?А?А?А?";
        CHECK_THROW(pointer->encrypt(open_text),cipher_error);
    }
    TEST_FIXTURE(KeyAB_fixture,TextWithASpace ) {
        wstring open_text = L"ПРОСТО ТЕКСТ";
        CHECK_THROW(pointer->encrypt(open_text),cipher_error);
    }

}
SUITE(DecryptTest)
{
    TEST_FIXTURE(KeyAB_fixture, LargeLetters) {
        wstring cipher_text = L"ПРОСТОТЕКСТ";
        wstring result_correct = L"ПРОСТОТЕКСТ";
        CHECK_EQUAL(true, result_correct == pointer->decrypt(cipher_text));
    }
    TEST_FIXTURE(KeyAB_fixture, Smallletters) {
        wstring cipher_text = L"ПростоТекст";
        wstring result_correct = L"ПРОСТОТЕКСТ";
        CHECK_EQUAL(true, result_correct == pointer->decrypt(cipher_text));
    }

    TEST_FIXTURE(KeyAB_fixture, EmptyText) {
        wstring cipher_text = L"12345";
        CHECK_THROW(pointer->decrypt(cipher_text),cipher_error);
    }

    TEST_FIXTURE(KeyAB_fixture,TextWithSymbol) {
        wstring cipher_text = L"А?А?А?А?";
        CHECK_THROW(pointer->decrypt(cipher_text),cipher_error);
    }
    TEST_FIXTURE(KeyAB_fixture,TextWithASpace ) {
        wstring cipher_text = L"ПРОСТО ТЕКСТ";
        CHECK_THROW(pointer->decrypt(cipher_text),cipher_error);
    }
}
int main()
{
    return UnitTest::RunAllTests();
}
