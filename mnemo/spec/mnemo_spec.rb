
require 'spec_helper'


describe './mnemo 0' do

  it 'exits with 0' do

    result = run('./mnemo 0')

    result.exit_status.should == 0
  end
end

