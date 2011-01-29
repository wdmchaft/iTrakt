###############################
#
# The actual mappings
#

mappings = lambda do
  map('/hello') do
    serve_text_fixture('hello-world')
  end

  map('/json/simple-array') do
    serve_json_fixture('simple-array')
  end

  map('/json/simple-dictionary') do
    serve_json_fixture('simple-dictionary')
  end

  map('/poster.jpg') do
    serve_jpeg_fixture('poster')
  end

  map('/user/calendar/shows.json/secret/bob') do
    serve_json_fixture('user-calendar-shows')
  end
end


###############################
#
# The implementation, boring...
#

FIXTURES = File.dirname(__FILE__)

module FixtureServe
  extend self

  def map(path, &block)
    @mappings ||= {}
    @mappings[path] = block
  end

  def call(env)
    _, block = @mappings.find { |path, _| path === env['PATH_INFO'] }
    block ? block.call : ohnoes_404!
  end

  private

  def fixture(name)
    File.join(FIXTURES, name)
  end

  def fixture_io(name)
    File.open(fixture(name), 'r')
  end

  def serve_text_fixture(name)
    [200, { 'Content-Type' => 'text/plain' }, fixture_io("#{name}.txt")]
  end

  def serve_json_fixture(name)
    [200, { 'Content-Type' => 'application/json' }, fixture_io("#{name}.json")]
  end

  def serve_jpeg_fixture(name)
    [200, { 'Content-Type' => 'image/jpeg' }, fixture_io("#{name}.jpg")]
  end

  def ohnoes_404!
    [404, { 'Content-Type' => 'text/plain' }, ['404 fixture not found']]
  end
end

FixtureServe.instance_eval(&mappings)

run FixtureServe