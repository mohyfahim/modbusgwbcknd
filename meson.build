project('modbusgwbcknd', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++17'])



libdeps = [dependency('libmodbus'),
          dependency('jsoncpp'),
          dependency('libulfius'),
          dependency('sqlite3')]

incdir = include_directories('lib/sqlite_orm/include', 'src')

sources = ['src/server.cpp', 'src/routes/user/user.cpp']

executable('mgbcknd', sources, dependencies: libdeps, include_directories: incdir)