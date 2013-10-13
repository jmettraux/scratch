
require 'spec_helper'


class JhnValue < FFI::Struct
  layout(
    :type, :char,
    :value, :pointer)
end

module Jhn
  extend FFI::Library

  ffi_lib File.expand_path(File.dirname(__FILE__) + '/../libjohn.so')

  attach_function :jhn_value_tol, [ JhnValue.by_value ], :long
  attach_function :jhn_value_tos, [ JhnValue.by_value ], :string
end


describe 'libjohn.so' do

  describe 'jhn_value_tol()' do

    it 'returns -1 if the value is not a number' do

      val = JhnValue.new
      val[:type] = 's'.bytes.first
      val[:value] = FFI::Pointer::NULL

      Jhn.jhn_value_tol(val).should == -1
    end

    it 'returns a long' do

      val = JhnValue.new
      val[:type] = 'n'.bytes.first
      val[:value] = FFI::MemoryPointer.new(:long)
      val[:value].put_int32(0, 1234567)

      Jhn.jhn_value_tol(val).should == 1234567
    end
  end

  describe 'jhn_value_tos()' do

    it 'returns nil if the value is not a string' do

      val = JhnValue.new
      val[:type] = 'n'.bytes.first
      val[:value] = FFI::Pointer::NULL

      Jhn.jhn_value_tos(val).should == nil
    end

    it 'returns a string' do

      val = JhnValue.new
      val[:type] = 's'.bytes.first
      val[:value] = FFI::MemoryPointer.new(:string)
      val[:value].write_string('nada')

      Jhn.jhn_value_tos(val).should == 'nada'
    end
  end
end

