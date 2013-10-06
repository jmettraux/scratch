
unless $made
  puts
  puts `make`
  puts
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

module Mne
  extend FFI::Library

  ffi_lib File.expand_path(File.dirname(__FILE__) + '/../libmnemo.so')

  attach_function :mne_tos, [ :long ], :string
end


#RSpec.configure do |config|
#end

