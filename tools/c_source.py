"""Extract complete C definitions without relying on brace indentation."""

import re


def _definition_bounds(text, name):
    """Find the signature, opening brace and exclusive end in unmasked text."""
    masked = re.sub(r"/\*.*?\*/|//[^\n]*|\"(?:\\.|[^\"\\])*\"|'(?:\\.|[^'\\])*'",
                    lambda match: re.sub(r'[^\n]', ' ', match.group(0)), text, flags=re.S)
    match = re.search(r"^[^\n;{}#]*\b" + re.escape(name) + r"\s*\([^;{]*\)\s*\{", masked, re.M)
    if match is None:
        raise ValueError(f"No definition of {name} found")
    opening = masked.rfind('{', match.start(), match.end())
    depth = 0
    for position in range(opening, len(masked)):
        depth += masked[position] == '{'
        depth -= masked[position] == '}'
        if depth == 0:
            return match.start(), opening, position + 1
    raise ValueError(f"Unclosed definition of {name}")


def function_definition(text, name):
    """Return the named definition, including nested blocks and its final brace."""
    start, _, end = _definition_bounds(text, name)
    return text[start:end]


def function_body_lines(text, name):
    """Return zero-based opening/closing brace lines for the selected body."""
    _, opening, end = _definition_bounds(text, name)
    return text.count('\n', 0, opening), text.count('\n', 0, end - 1)
