project(
  'Lab2', 'cpp',
  version : '0.1.0',
  default_options : [
    'warning_level=3',
    'cpp_std=c++11'
  ])

sources = files([
  'main.cpp',
  'src/cart.cpp',
  'src/flows.cpp',
  'src/item.cpp',
  'src/store.cpp',
  'src/ui.cpp',
  'src/structures/list.cpp',
  'src/structures/map.cpp',
  'src/structures/queue.cpp',
  'src/structures/tree.cpp',
])

exe = executable(
  'team-project', sources,
  include_directories : include_directories('include'),
  install : true)
