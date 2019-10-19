# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added

- QML based application for Sailfish OS

### Changed
- application name from LeitnerLearner to BibleByByte
- backport to C++11 since Sailfish OS (as of 3.0.3)  does not support C++17 yet
- identify stored bible verses by their technical title

### Fixed
- display widget in check not being hidden when a new data item is being checked

## [1.0.0] - 2019-05-25
First public release!

### Added
- Qt Widgets application for learning bible verses by a modified version of the Leitner system


[Unreleased]: https://github.com/markuspg/BibleByByte/compare/v1.0.0...HEAD
[1.0.0]: https://github.com/markuspg/BibleByByte/releases/tag/v1.0.0
