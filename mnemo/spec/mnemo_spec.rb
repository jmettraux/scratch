
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

describe 'mne_tos()' do

  it 'turns longs to mnemonic strings' do

    Mne.mne_tos(0).should == 'a'
    Mne.mne_tos(1).should == 'i'
    Mne.mne_tos(-1).should == 'wii'

    # so, who frees the strings?

    Mne.mne_tos(-1).class.should == String
  end
end

