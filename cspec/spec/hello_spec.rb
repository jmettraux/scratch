
require 'spec_helper'


describe './hello' do

  it 'exits with 0' do

    result = run('./hello')

    result.exit_status.should == 0
  end
end

