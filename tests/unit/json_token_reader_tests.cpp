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

