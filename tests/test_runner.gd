extends SceneTree


static func files_in_dir(path, extension = null):
	var files = []
	var dir = Directory.new()
	dir.open(path)
	dir.list_dir_begin()

	while true:
		var file = dir.get_next()
		if file == "":
			break
		if not file.begins_with("."):
			if extension == null:
				files.append(file)
			elif file.get_extension() == str(extension):
				files.append(file)
	dir.list_dir_end()
	return files

var paths = [
	"tests/scripts/",
]

var count = 0

func _init():

	print("\nSTART TESTING")

	for path in paths:
		print("\n" + path)
		var scripts = files_in_dir(path, "gd")
		for script in scripts:
			count += 1
			print("\t[" + str(count) + "/" + str(scripts.size()) + "] " + script)
			load(path + script).new()
		count = 0

	print("\nDONE TESTING\n")

	quit()
