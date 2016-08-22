#!/usr/bin/python
import sys
import xml.etree.ElementTree as ET

def main():
	if len(sys.argv) != 3:
		print("Usage: process_glade <path to glade file> <path to output>");
		return 1;

	tree = ET.parse(sys.argv[1]);
	root = tree.getroot();

	for ob in root.findall('.//object'):
		for child in ob:
			if child.get("name") == "name":
				ob.remove(child);
				continue;

		name = ob.get("id");
		prop = ET.Element("property");
		prop.set("name", "name");
		prop.text = name;
		ob.insert(0, prop);

	tree.write(sys.argv[2]);

main();
