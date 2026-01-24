# Contributing Guidelines

## Account and Access Control
- Members must **not** self-register. Only administrators can create member accounts via the admin flow.

## Code Style
- Use C++14.
- Prefer standard headers and avoid unnecessary `using namespace std;` in headers where possible.
- Keep data structures consistent with the current design (BST for games, linked lists where specified, hash/linked list for members as agreed by the team).

## Functional Responsibilities
- Admin flows: manage games, manage members, view borrow summaries.
- Member flows: borrow/return games, view personal summaries; no self-registration.

## Testing
- Provide simple console-driven test paths for new features.
- Validate inputs and handle missing/invalid records gracefully.