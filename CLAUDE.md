# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) and other AI assistants when working in this repository.

---

## Repository Overview

**Repository:** isaacjuan/Sync
**Status:** Active development.
**Purpose:** REST API backend written in C++ using the Crow framework.
**Tech stack:** C++17, Crow v1.0+5, CMake 3.16+

---

## Git Workflow

### Branch Naming
- Feature branches: `feature/<short-description>`
- Bug fixes: `fix/<short-description>`
- Documentation: `docs/<short-description>`
- Claude-generated branches: `claude/<task-description>-<session-id>`

### Commit Messages
Use the conventional commits format:
```
<type>(<scope>): <short summary>

[optional body]

[optional footer(s)]
```

Types: `feat`, `fix`, `docs`, `style`, `refactor`, `test`, `chore`, `ci`

Examples:
```
feat(auth): add JWT token refresh logic
fix(api): handle null response from upstream service
docs: add CLAUDE.md with project conventions
```

### Push Protocol
- Always push with tracking: `git push -u origin <branch-name>`
- Never force-push to `main` or `master`
- Claude branches must follow the format: `claude/<description>-<session-id>`

### Pull Requests
- Keep PRs focused and small when possible
- Include a clear description of what changed and why
- Link related issues in the PR body

---

## Development Workflow

### Project Structure
```
sync-backend/
├── CMakeLists.txt          # Build definition; FetchContent pulls Crow
├── src/
│   ├── main.cpp            # Entry point — registers routes, starts server
│   └── routes/
│       ├── health.hpp/.cpp # GET /health
│       └── items.hpp/.cpp  # CRUD /items
└── include/                # Public headers (add as project grows)
```

### Getting Started

**Prerequisites:** CMake ≥ 3.16, a C++17-capable compiler (GCC 9+, Clang 10+), git, and an internet connection (FetchContent downloads Crow on first build).

```bash
# 1. Clone
git clone <repo-url> && cd sync-backend

# 2. Configure (Debug build)
cmake -B build -DCMAKE_BUILD_TYPE=Debug

# 3. Compile
cmake --build build -j$(nproc)

# 4. Run (listens on :8080)
./build/sync-backend
```

**Quick smoke test:**
```bash
curl http://localhost:8080/health
curl -X POST http://localhost:8080/items -d '{"name":"widget"}' -H 'Content-Type: application/json'
curl http://localhost:8080/items
```

### Adding a New Route Module
1. Create `src/routes/<module>.hpp` and `src/routes/<module>.cpp`
2. Define a `register_<module>_routes(crow::SimpleApp& app)` function
3. Call it from `src/main.cpp`
4. CMake picks up the new `.cpp` automatically via `file(GLOB_RECURSE)`

### Environment Setup
- The server port defaults to `8080` (set in `src/main.cpp`)
- Never commit `.env` files containing secrets
- Document all required environment variables in `.env.example` if added

---

## Code Conventions

### C++ Style
- Standard: **C++17**
- Naming: `snake_case` for variables, functions, files; `PascalCase` for types/classes
- Use `#pragma once` for include guards
- Prefer `const` and `constexpr` where applicable
- Use `std::mutex` + `std::lock_guard` for any shared mutable state (the in-memory store uses this pattern)
- No raw `new`/`delete` — use smart pointers (`std::unique_ptr`, `std::shared_ptr`) or value semantics

### Route Conventions
- Each resource gets its own `.hpp`/`.cpp` pair under `src/routes/`
- Route functions are named `register_<resource>_routes(crow::SimpleApp&)`
- Return JSON with appropriate HTTP status codes; never return 200 on error
- Validate all fields from `req.body` before use

### General
- Prefer clarity over cleverness
- Write self-documenting code; add comments only where logic is non-obvious
- Keep functions small and focused on a single responsibility
- Validate at system boundaries (user input, external APIs); trust internal code

### File Organization
- Group by feature/resource under `src/routes/`
- Keep configuration files at the project root
- Place tests in a parallel `tests/` directory (when added)

### Error Handling
- Handle errors explicitly; avoid swallowing exceptions silently
- Return meaningful JSON error objects: `{"error": "<description>"}`
- Use appropriate HTTP status codes (400 bad request, 404 not found, 500 server error)

### Security
- Never hardcode secrets, API keys, or credentials
- Validate and sanitize all request body fields before use
- Follow OWASP Top 10 guidelines
- Use parameterized queries for all database access (when a DB is added)

---

## Testing

No test framework is configured yet. Recommended path: add **Google Test** via FetchContent and create a `tests/` directory at the root.

General guidelines (apply when tests are added):
- Write tests for all non-trivial logic
- Aim for tests that are fast, isolated, and deterministic
- Use descriptive test names that explain the expected behavior
- Run the full test suite before pushing changes

---

## Linting and Formatting

Recommended tools (not yet configured):
- **clang-format** for formatting — run `clang-format -i src/**/*.cpp src/**/*.hpp`
- **clang-tidy** for static analysis

General guidelines:
- Run linting before committing: ensure zero lint errors
- Do not reformat files outside the scope of your change
- Linting and formatting checks should pass in CI before merging

---

## CI/CD

Update this section once CI/CD pipelines are configured. General guidelines:

- All checks (lint, test, build) must pass before merging PRs
- Do not bypass CI with `--no-verify` or similar flags unless explicitly authorized
- Keep CI pipelines fast; parallelize jobs where possible

---

## AI Assistant Guidelines

When Claude Code or another AI assistant works in this repository:

1. **Read before editing** — Always read a file before modifying it
2. **Minimal changes** — Only change what is necessary for the task; avoid scope creep
3. **No unnecessary files** — Do not create files (especially docs/READMEs) unless explicitly asked
4. **No secrets** — Never commit credentials, API keys, or sensitive data
5. **Ask when uncertain** — If a requirement is ambiguous, ask for clarification before implementing
6. **Test your changes** — Run relevant tests after making changes; report results
7. **Conventional commits** — Use the commit format described above
8. **Branch discipline** — Develop on the designated branch; never push to main without authorization
9. **Reversible actions** — Prefer reversible actions; confirm with the user before destructive operations (force push, file deletion, etc.)
10. **Update this file** — Keep CLAUDE.md current as the project evolves

---

## Updating This File

This file should be updated whenever:
- A new tech stack or framework is adopted
- New tooling (linter, formatter, test runner) is added
- Significant architectural decisions are made
- New team conventions are established

Last updated: 2026-02-27
