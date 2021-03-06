
require 'spec_helper'


#describe './mnemo 0' do
#
#  it 'exits with 0' do
#
#    result = run('./mnemo 0')
#
#    result.exit_status.should == 0
#  end
#end

class MneTolResult < FFI::Struct

  layout :err, :int, :result, :long
end

module Mne
  extend FFI::Library

  ffi_lib File.expand_path(File.dirname(__FILE__) + '/../libmnemo.so')

  attach_function :mne_tos, [ :long ], :string
  attach_function :mne_tol, [ :string ], MneTolResult.by_value
  attach_function :mne_ismnemo, [ :string ], :int
end


describe 'mne_tos()' do

  it 'turns longs to mnemonic strings' do

    Mne.mne_tos(0).should == 'a'
    Mne.mne_tos(1).should == 'i'
    Mne.mne_tos(47).should == 'ia'
    Mne.mne_tos(-1).should == 'wii'
    Mne.mne_tos(1234567).should == 'shirerete'

    # so, who frees the strings?

    Mne.mne_tos(-1).class.should == String
  end
end

describe 'mne_tol()' do

  it 'turns strings to longs' do

    Mne.mne_tol('')[:err].should == 1

    Mne.mne_tol('a')[:result].should == 0
    Mne.mne_tol('i')[:result].should == 1
    Mne.mne_tol('ia')[:result].should == 47
    Mne.mne_tol('wii')[:result].should == -1
    Mne.mne_tol('shirerete')[:result].should == 1234567
  end
end

describe 'mne_ismnemo()' do

  it 'returns -1 on an nil string' do

    Mne.mne_ismnemo(nil).should == -1
  end

  it 'returns 1 when true, 0 else' do

    Mne.mne_ismnemo('').should == 0
    Mne.mne_ismnemo('a').should == 1
    Mne.mne_ismnemo('ia').should == 1
    Mne.mne_ismnemo('wii').should == 1
    Mne.mne_ismnemo('shirerete').should == 1
    Mne.mne_ismnemo('shit').should == 0
  end
end

