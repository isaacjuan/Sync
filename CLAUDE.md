# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) and other AI assistants when working in this repository.

---

## Repository Overview

**Repository:** isaacjuan/Sync
**Status:** Initialized — no source code committed yet.
**Purpose:** To be determined as the project evolves. Update this section once the project's intent is clear.

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

### Getting Started
Since this repository is new, the first steps will typically be:
1. Clone the repository
2. Install project dependencies (update this section once a tech stack is chosen)
3. Configure environment variables (copy `.env.example` to `.env` if applicable)
4. Run the development server

### Environment Setup
- Copy `.env.example` to `.env` and fill in required values (if applicable)
- Never commit `.env` files containing secrets
- Document all required environment variables in `.env.example`

---

## Code Conventions

These conventions apply generally and should be refined as the project's tech stack is established.

### General
- Prefer clarity over cleverness
- Write self-documenting code; add comments only where logic is non-obvious
- Keep functions small and focused on a single responsibility
- Validate at system boundaries (user input, external APIs); trust internal code

### File Organization
- Group related files by feature/domain, not by file type, where practical
- Keep configuration files at the project root
- Place tests adjacent to the code they test, or in a parallel `tests/` directory

### Error Handling
- Handle errors explicitly; avoid swallowing exceptions silently
- Log errors with enough context to diagnose the issue
- Return meaningful error messages to callers/users

### Security
- Never hardcode secrets, API keys, or credentials
- Sanitize all user input before use
- Follow OWASP Top 10 guidelines
- Use parameterized queries for all database access

---

## Testing

Update this section once a testing framework is chosen. General guidelines:

- Write tests for all non-trivial logic
- Aim for tests that are fast, isolated, and deterministic
- Use descriptive test names that explain the expected behavior
- Run the full test suite before pushing changes

---

## Linting and Formatting

Update this section once tooling is configured. General guidelines:

- Run linting before committing: ensure zero lint errors
- Use the project's configured formatter (e.g., Prettier, Black, rustfmt) — do not reformat files outside the scope of your change
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

Last updated: 2026-02-26
