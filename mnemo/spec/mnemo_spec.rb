
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

module Mne
  extend FFI::Library

  ffi_lib File.expand_path(File.dirname(__FILE__) + '/../libmnemo.so')

  attach_function :mne_tos, [ :long ], :string
  attach_function :mne_tol, [ :string ], :long
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

    Mne.mne_tol('').should == 0
    Mne.mne_tol('a').should == 0
    Mne.mne_tol('i').should == 1
    Mne.mne_tol('ia').should == 47
    Mne.mne_tol('wii').should == -1
    Mne.mne_tol('shirerete').should == 1234567
  end
end

