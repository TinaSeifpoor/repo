import os
import sys
from django.http import request
from os import rename
import requests
import shutil

with open('d:/genderOut.txt', 'a') as proc_seqf:
	lines = open('d:/gender.txt').read().splitlines()
	for line in lines:
		result = requests.get("http://api.genderize.io?name=%s" % line)
		result = result.json()
		try:
			proc_seqf.write("{}\t{}\t{}\t{}\n".format(result['name'], result['gender'], result['probability'], result['count']))
		except Exception as e:
			print(line)
