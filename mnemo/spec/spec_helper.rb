
unless $made
  puts
  puts `make`
  puts
  exit 1 if $?.exitstatus != 0
  $made = true
end

class Result

  attr_accessor :out
  attr_accessor :status

  def exitstatus; @status.exitstatus; end
  def exit_status; @status.exitstatus; end

  def self.run(elts)

    r = Result.new

    r.out = `#{elts.join(' ')}`
    r.status = $?

    r
  end
end

def run(*elts)

  Result.run(elts)
end


require 'ffi'


#RSpec.configure do |config|
#end

