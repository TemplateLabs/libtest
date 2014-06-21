require 'rake/clean'

TEST_SOURCES = FileList['test/**/*.cc']
TEST_OBJS = TEST_SOURCES.pathmap("%{^test/,build/}X.o")
CLEAN.include TEST_OBJS

CC = 'cc'
INCDIRS = '.'.pathmap('-I%p')

CXXFLAGS = %w[-std=c++11].join ' '

def source_for_object(name)
    base_name = name.pathmap("%{^build/,test/}X")
    TEST_SOURCES.find {|f| f.ext('') == base_name }
end

rule '.o' => ->(name){ source_for_object(name) } do |t|
    sh "#{CC} #{INCDIRS} #{CXXFLAGS} -c -o #{t.name} #{t.source}"
end

directory 'build'
CLEAN << 'build'

file 'build/test' => ['build', *TEST_OBJS] do |task|
    sh "cc -lstdc++ -o #{task.name} #{task.sources.drop(1).join(' ')}"
end
CLOBBER << 'build/test'

task :default => :test

task test:'build/test' do
    sh "build/test"
end
