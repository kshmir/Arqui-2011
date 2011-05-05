# A sample Guardfile
# More info at https://github.com/guard/guard#readme

# Add files and commands to this file, like the example:
#   watch('file/path') { `command(s)` }
#

if !RUBY_PLATFORM.match(/darwin/)
	puts "Guarding src"
	guard 'shell' do
	  watch(/(src|include)\/.*/) {|m| 
			puts "Compiling... #{m}"
			`$PWD/compila` 
			puts "DONE!"
		}
	end
end
if RUBY_PLATFORM.match(/darwin/) || File.exists?(".vmoverride")
	puts "Guarding bin"
	guard 'shell' do
	  watch(/bin\/.*/) {|m| `$PWD/arma` }
	end
end


