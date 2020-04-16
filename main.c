/*
 *	MetaCall Embedding NodeJS Example by Parra Studios
 *	An example of embedding NodeJS into C/C++.
 *
 *	Copyright (C) 2016 - 2020 Vicente Eduardo Ferrer Garcia <vic798@gmail.com>
 *
 *	Licensed under the Apache License, Version 2.0 (the "License");
 *	you may not use this file except in compliance with the License.
 *	You may obtain a copy of the License at
 *
 *		http://www.apache.org/licenses/LICENSE-2.0
 *
 *	Unless required by applicable law or agreed to in writing, software
 *	distributed under the License is distributed on an "AS IS" BASIS,
 *	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *	See the License for the specific language governing permissions and
 *	limitations under the License.
 *
 */

#include <metacall/metacall.h>
#include <stdio.h>

static int cleanup(int code)
{
	if (metacall_destroy() != 0)
	{
		return code != 0 ? -code : -255;
	}

	return code;
}

int sum(double a, double b)
{
	// Parameters to be passed to the sum function
	void * args[] =
	{
		metacall_value_create_double(a), metacall_value_create_double(b)
	};

	void * ret = NULL;

	// Call to sum function
	ret = metacallv("sum", args);

	// Clean up arguments
	for (size_t it = 0; it < sizeof(args) / sizeof(args[0]); ++it)
	{
		metacall_value_destroy(args[it]);
	}

	if (ret == NULL)
	{
		return 1;
	}

	printf("Function sum returned: %f\n", metacall_value_to_double(ret));

	// Clean up return value
	metacall_value_destroy(ret);

	return 0;
}

int main(int argc, char *argv[])
{
	struct metacall_log_stdio_type log_stdio = { stdout };

	printf(metacall_print_info());

	// Define log stream
	if (metacall_log(METACALL_LOG_STDIO, (void *)&log_stdio) != 0)
	{
		return cleanup(1);
	}

	// Initialize MetaCall
	if (metacall_initialize() != 0)
	{
		return cleanup(2);
	}

	// NodeJS
	{
		// Array of scripts to be loaded by MetaCall
		const char * js_scripts[] =
		{
			"script.js"
		};

		// Load scripts
		if (metacall_load_from_file("node", js_scripts, sizeof(js_scripts) / sizeof(js_scripts[0]), NULL) != 0)
		{
			return cleanup(3);
		}

		// Execute sum function
		if (sum(3, 4) != 0)
		{
			return cleanup(4);
		}
	}

	return cleanup(0);
}
