
#include <../mnemo/mnemo.h>

//describe 'mne_tos()' do
//
//  it 'turns longs to mnemonic strings' do
//
//    Mne.mne_tos(0).should == 'a'
//    Mne.mne_tos(1).should == 'i'
//    Mne.mne_tos(47).should == 'ia'
//    Mne.mne_tos(-1).should == 'wii'
//    Mne.mne_tos(1234567).should == 'shirerete'
//
//    # so, who frees the strings?
//
//    Mne.mne_tos(-1).class.should == String
//  end
//end

describe "mne_tos()"
{
  context "cows are flying"
  {
    it "turns longs to mnemonic (hopefully) strings"
    {
      ensure mne_to_s(0) == "a"
      ensure(mne_to_s(1) == "i")
      ensure(mne_to_s(47) == "ia")
      ensure(mne_to_s(-1) == "wii")
      ensure(mne_to_s(1234567) == "shirerete")
    }
  }
}

