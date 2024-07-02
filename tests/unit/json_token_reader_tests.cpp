#include <gtest/gtest.h>

#include "json_token_reader.h"

TEST(JsonTokenReader, CannotAdvanceInEmptyJson) {
    json::__internal::JsonTokenReader reader("");
    EXPECT_FALSE(reader.hasNext());
}

TEST(JsonTokenReader, CanAdvanceInNonEmptyJson) {
    json::__internal::JsonTokenReader reader("1");
    EXPECT_TRUE(reader.hasNext());
}

TEST(JsonTokenReader, ReachingEofReturnsFalse) {
    json::__internal::JsonTokenReader reader("1");

    EXPECT_TRUE(reader.next());
    EXPECT_FALSE(reader.next());
}

TEST(JsonTokenReader, PeekingValueReturnsCorrectCharacter) {
    json::__internal::JsonTokenReader reader("1a");
    EXPECT_EQ('1', reader.peek());
}

TEST(JsonTokenReader, PeekingAtEofReturnsTokenEOF) {
    json::__internal::JsonTokenReader reader("");
    EXPECT_EQ(json::__internal::JsonTokenReader::TOKEN_EOF, reader.peek());
}

TEST(JsonTokenReader, ConsumeReturnsTrueIfCharactersHaveMatched) {
    json::__internal::JsonTokenReader reader("abc");
    EXPECT_TRUE(reader.consume('a'));
}

TEST(JsonTokenReader, ConsumeReturnsFalseIfCharactersHaveNotMatched) {
    json::__internal::JsonTokenReader reader("abc");
    EXPECT_FALSE(reader.consume('b'));
}

TEST(JsonTokenReader, ConsumeReturnsFalseIfReachedEndOfTheStream) {
    json::__internal::JsonTokenReader reader("abc");

    reader.next();
    reader.next();
    reader.next();

    EXPECT_FALSE(reader.hasNext());
    EXPECT_FALSE(reader.consume('a'));
}

TEST(JsonTokenReader, ConsumeAllReturnsTrueIfTheEntirePatternMatched) {
    json::__internal::JsonTokenReader reader("spatterne");

    reader.next();

    EXPECT_TRUE(reader.consumeAll("pattern"));
}

TEST(JsonTokenReader, ConsumeAllReturnsFalseIfPatternHasNotMatched) {
    json::__internal::JsonTokenReader reader("spatterne");
    reader.next();

    EXPECT_FALSE(reader.consumeAll("abc"));
}

TEST(JsonTokenReader, ConsumeAllReturnsFalseIfPatternIsPartiallyMatched) {
    json::__internal::JsonTokenReader reader("spatterne");
    reader.next();

    EXPECT_FALSE(reader.consumeAll("patbcd"));
}

TEST(JsonTokenReader, ConsumeAllReturnsFalseIfReachedEndOfTheStream) {
    json::__internal::JsonTokenReader reader("spat");
    reader.next();

    EXPECT_FALSE(reader.consumeAll("pattern"));
}

TEST(JsonTokenReader, SaveAndRestoreReturnsReaderToInitialState) {
    json::__internal::JsonTokenReader reader("really long string");

    reader.next();
    reader.next();

    EXPECT_EQ('a', reader.peek());

    const auto& token = reader.save();

    reader.next();
    reader.next();
    reader.next();

    EXPECT_EQ('y', reader.peek());

    reader.restore(token);
    EXPECT_EQ('a', reader.peek());
}


