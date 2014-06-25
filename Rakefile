require 'rake/clean'

TEST_SOURCES = FileList['test/**/*.cc']
TEST_OBJS = TEST_SOURCES.pathmap("%{^test/,build/}X.o")
CLEAN.include TEST_OBJS

CC = ENV['CXX'] || 'cc'
INCDIRS = '.'.pathmap('-I%p')

CFLAGS = %w[-Wdeprecated -Wdeprecated-declarations -Wshadow -Wall -W -Werror -Wfloat-equal -Wundef -Wendif-labels].join ' '
CXXFLAGS = %w[-std=c++11].join ' '

def source_for_object(name)
    base_name = name.pathmap("%{^build/,test/}X")
    TEST_SOURCES.find {|f| f.ext('') == base_name }
end

rule '.o' => ->(name){ source_for_object(name) } do |t|
    sh "#{CC} #{INCDIRS} #{CFLAGS} #{CXXFLAGS} -c -o #{t.name} #{t.source}"
end

directory 'build'
CLEAN << 'build'

TEST_OBJS.each do |f|
    directory f.pathmap('%d')
    file f => f.pathmap('%d')
end

file 'build/test' => TEST_OBJS do |task|
    sh "#{CC} -lstdc++ -o #{task.name} #{task.sources.join ' '}"
end
CLOBBER << 'build/test'

task :default => :test

task test:['build', 'build/test'] do
    sh "build/test"
end
