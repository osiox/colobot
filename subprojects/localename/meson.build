project('localename', ['c'])

_localename_src = [
    'localename.c'
]

_liblocalename = static_library(
    'localename',
    _localename_src
)

localename_dep = declare_dependency(
    link_with: _liblocalename,
    include_directories: '.'
)
