#pragma once

#include "LineReader.h"

#include <replxx.hxx>


class ReplxxLineReader : public LineReader
{
public:
    ReplxxLineReader(
        Suggest & suggest,
        const String & history_file_path,
        bool multiline,
        Patterns extenders_,
        Patterns delimiters_,
        replxx::Replxx::highlighter_callback_t highlighter_);
    ~ReplxxLineReader() override;

    void enableBracketedPaste() override;

private:
    InputStatus readOneLine(const String & prompt) override;
    void addToHistory(const String & line) override;
    int executeEditor(const std::string & path);
    void openEditor();

    replxx::Replxx rx;
    replxx::Replxx::highlighter_callback_t highlighter;

    // used to call flock() to synchronize multiple clients using same history file
    int history_file_fd = -1;
    bool bracketed_paste_enabled = false;

    std::string editor;
};
