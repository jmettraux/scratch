
#def sign(meth, uri, headers, body)
#
#  headers['date'] ||= Time.now.rfc822
#
#  if body
#
#    headers['content-type'] =
#      if body.match(/^<\?xml/)
#        #'multipart/form-data'
#        'application/xml'
#      else
#        'text/plain'
#      end
#    #headers['content-type'] = 'text/plain' unless body.match(/^<\?xml/)
#
#    headers['content-md5'] =
#      Base64.encode64(Digest::MD5.digest(body)).strip
#  end
#
#  headers['authorization'] =
#    [
#      "AWS #{@aki}",
#      Base64.encode64(
#        OpenSSL::HMAC.digest(
#          OpenSSL::Digest.new('SHA1'),
#          @sak,
#          string_to_sign(meth, uri, headers)
#        )
#      ).strip
#    ].join(':')
#end

require 'base64'
require 'openssl'

d = OpenSSL::Digest::MD5.digest('toto')
puts d
puts Base64.encode64(d)


