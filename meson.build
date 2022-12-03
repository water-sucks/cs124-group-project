project(
  'Lab2', 'cpp',
  version : '0.1.0',
  default_options : [
    'warning_level=3',
    'cpp_std=c++11'
  ])

sources = files([
  'main.cpp',
  'src/store.cpp',
  'src/structures/list.cpp'
])

exe = executable(
  'team-project', sources,
  include_directories : include_directories('include'),
  install : true)