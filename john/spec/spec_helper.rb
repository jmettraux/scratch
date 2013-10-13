
unless $made
  puts
  puts(`make`)
  puts
  exit 1 if $?.exitstatus != 0
  $made = true
end

require 'ffi'


#RSpec.configure do |config|
#end

