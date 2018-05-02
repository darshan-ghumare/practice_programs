
def parse_line(line):
  """
  Parse line from the file.
  Ex. Mail App, Authentication API, v6 then
      return ("Mail App", "Authentication API", 6).
  Args:
    line (str): Line fron the file.
  Returns:
    record((str, str, int)): (App name, API name, API version).
  """
  app_name, api_name, api_ver_str = line.split(",")
  return (app_name.strip(),
          api_name.strip(),
          # Strip leadng 'v' and convert version to int.
          int(api_ver_str.strip()[1:]))

def build_map(lines):
  """
  Build map of API Name => List of App names using oldest API version.

  Args:
    lines ([ str ]): List if lines from the files.
  Returns:
    api_usage_map ({str: {int: [ str ]}}): Map of API name to APP using its
        oldest version.
  """
  api_usage_map = {}
  print "len lines ", len(lines)
  for line in lines:
    app_name, api_name, api_ver = parse_line(line)
    if api_name not in api_usage_map:
      # API name occurred first time.
      api_usage_map[api_name] = (1, api_ver, [ app_name ])
    else:
      total_api_vers, oldest_api_ver, app_name_list = api_usage_map[api_name]
      if oldest_api_ver > api_ver:
        total_api_vers += 1
        # Found older API version usage.
        api_usage_map[api_name] = (total_api_vers, api_ver, [ app_name ])
      elif oldest_api_ver == api_ver and app_name not in app_name_list:
        # Found another oldest API usage.
        app_name_list.append(app_name)
        api_usage_map[api_name] = (total_api_vers, api_ver, app_name_list)
      elif oldest_api_ver != api_ver:
        # Found newer version of API usage.
        total_api_vers += 1
        api_usage_map[api_name] = (total_api_vers,
                                   oldest_api_ver,
                                   app_name_list)

  return api_usage_map

def main(argv):
  assert len(argv) == 2

  # Read file as list of lines.
  with open(argv[1], "r") as fh:
    lines = fh.read().splitlines()

  # Build map of API Name => List of App names using that API for each version.
  api_usage_map = build_map(lines)
  print "******** OUTPUT *********"
  for k, v in api_usage_map.iteritems():
    total_api_vers, oldest_api_ver, app_name_list = v
    if total_api_vers > 1:
      print "API Name: ", k, "Oldest version: ", oldest_api_ver, "APP Names: "
      for app_name in app_name_list:
        print app_name

if __name__ == "__main__":
  import sys
  sys.exit(main(sys.argv))
