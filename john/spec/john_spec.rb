
require 'spec_helper'


#class MneTolResult < FFI::Struct
#
#  layout :err, :int, :result, :long
#end
class JhnValue < FFI::Struct
  layout :type, :char
end

module Jhn
  extend FFI::Library

  ffi_lib File.expand_path(File.dirname(__FILE__) + '/../libjohn.so')

  attach_function :jhn_parse, [ :string ], JhnValue.by_ref
end


describe 'libjohn.so' do

  describe 'jhn_parse()' do

    it 'parses numbers' do

      v = Jhn.jhn_parse('1')
      v[:type].should == 'n'
    end

    it 'parses strings' do

      v = Jhn.jhn_parse('"a"')
      v[:type].should == 's'
    end
  end
end

