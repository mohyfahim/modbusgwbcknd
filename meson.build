project('modbusgwbcknd', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++17'])

cc = meson.get_compiler('cpp')




target_cpu = target_machine.cpu()

message('Host System Type:', target_cpu)

if target_cpu == 'x86_64'
  add_project_arguments('-DDEVELOP', language : 'cpp')
endif

libmbedtls_dep = dependency('mbedtls', required: false)

if not libmbedtls_dep.found()
    libmbedtls_dep = cc.find_library('mbedtls', dirs: '/usr/lib/x86_64-linux-gnu/', required: true)
    libmbedx509_dep = cc.find_library('mbedx509', dirs: '/usr/lib/x86_64-linux-gnu/', required: true)
    libmbedcrypto_dep = cc.find_library('mbedcrypto', dirs: '/usr/lib/x86_64-linux-gnu/', required: true)
endif

libdeps = [dependency('libmodbus'),
          dependency('jsoncpp'),
          dependency('libulfius'),
          dependency('jose'),
          dependency('jansson'),
          dependency('sqlite3')] + libmbedtls_dep + libmbedx509_dep + libmbedcrypto_dep

incdir = include_directories('lib/sqlite_orm/include', 'src')

sources = ['src/server.cpp', 'src/routes/user/user.cpp', 'src/utils/utils.cpp']

executable('mgbcknd', sources, dependencies: libdeps, include_directories: incdir)