/*  Clipboard - Cut, copy, and paste anything, anywhere, all from the terminal.
    Copyright (C) 2023 Jackson Huff and other contributors on GitHub.com
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.*/
#include <clipboard/gui.hpp>

std::ostream& operator<<(std::ostream& stream, ClipboardPathsAction const& action) {
    if (action == ClipboardPathsAction::Copy) {
        stream << "copy";
    } else if (action == ClipboardPathsAction::Cut) {
        stream << "cut";
    } else {
        stream << "unknown";
    }

    return stream;
}

ClipboardPaths::ClipboardPaths(std::vector<fs::path>&& paths, ClipboardPathsAction action)
        : m_action(action)
        , m_paths(std::move(paths)) {}

ClipboardPaths::ClipboardPaths(std::vector<fs::path> const& paths, ClipboardPathsAction action)
        : m_action(action)
        , m_paths(paths) {}

ClipboardContent::ClipboardContent(std::string const& text) : m_type(ClipboardContentType::Text), m_data(text) {}

ClipboardContent::ClipboardContent(std::string&& text) : m_type(ClipboardContentType::Text), m_data(std::move(text)) {}

ClipboardContent::ClipboardContent(ClipboardPaths const& paths) : m_type(ClipboardContentType::Paths), m_data(paths) {}

ClipboardContent::ClipboardContent(ClipboardPaths&& paths)
        : m_type(ClipboardContentType::Paths)
        , m_data(std::move(paths)) {}

ClipboardContent::ClipboardContent(std::vector<fs::path>&& paths, ClipboardPathsAction action)
        : ClipboardContent(ClipboardPaths(std::move(paths), action)) {}

ClipboardContent::ClipboardContent(std::vector<fs::path> const& paths, ClipboardPathsAction action)
        : ClipboardContent(ClipboardPaths(paths, action)) {}

ClipboardContent::ClipboardContent() : m_type(ClipboardContentType::Empty), m_data(nullptr) {}