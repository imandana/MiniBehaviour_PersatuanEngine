#include <mono/jit/jit.h>
#include <mono/metadata/object.h>
#include <mono/metadata/environment.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/debug-helpers.h>
#include <string.h>
#include <stdlib.h>
#include <vector>

#ifndef FALSE
#define FALSE 0
#endif

static void
call_methods (MonoObject *obj, char* pMethodName)
{
	MonoClass *klass;
	MonoDomain *domain;
	MonoMethod *method = NULL, *m = NULL, *ctor = NULL, *fail = NULL, *mvalues;
	void* iter;

	klass = mono_object_get_class (obj);
	domain = mono_object_get_domain (obj);

	/* retrieve all the methods we need */
	bool isThere=false;
	iter = NULL;
	while ((m = mono_class_get_methods (klass, &iter))) 
	{
		if (strcmp (mono_method_get_name (m), pMethodName) == 0) 
		{
			isThere=true;
			method = m;
		} 
	}
	if(isThere)
	mono_runtime_invoke (method, obj, NULL, NULL);
}

static void
	create_object (MonoDomain *domain, MonoImage *image, std::vector<MonoObject*>* objs)
{
	MonoClass *klass;
	//MonoClass *klassc;
	mono_bool cInterface = false;

	std::vector<MonoClass*> class_list;
	const MonoTableInfo* table_info =  mono_image_get_table_info(image, MONO_TABLE_TYPEDEF);

	int rows = mono_table_info_get_rows(table_info);
	for(int i=0; i< rows; i++)
	{
		MonoClass* _class =  nullptr;
		uint32_t cols[MONO_TYPEDEF_SIZE];
		mono_metadata_decode_row(table_info, i, cols, MONO_TYPEDEF_SIZE);
		const char* name = mono_metadata_string_heap(image, cols[MONO_TYPEDEF_NAME]);
		const char* name_space = mono_metadata_string_heap(image, cols[MONO_TYPEDEF_NAMESPACE]);
		_class = mono_class_from_name(image, name_space, name);
		class_list.push_back(_class);
	}
	uint32_t type_token=0;
	klass = mono_class_from_name (image, "PersatuanEngine", "MiniBehaviour");
	printf ( "Nama Classnya %s\n", mono_class_get_name (klass));

	printf ("%s\n ", mono_class_get_name (klass));

	if (!klass) {
		fprintf (stderr, "Can't find MiniBehaviour in assembly %s\n", mono_image_get_filename (image));
		exit (1);
	}

	for(int i =0; i < class_list.size(); i++)
	{
		if ( class_list[i]!= klass && mono_class_is_subclass_of (class_list[i], klass, cInterface)) 
				objs->push_back(mono_object_new (domain, class_list[i]));
	}
	//obj = mono_object_new (domain, klass);
	for(int i =0; i < objs->size(); i++)
	{
				mono_runtime_object_init ((*objs)[i]);
				//call_methods (objs[i]);
	}
}

static void main_function (MonoDomain *domain, const char *file, int argc, char **argv)
{
	MonoAssembly *assembly;
	assembly = mono_domain_assembly_open (domain, file);
	if (!assembly)
		exit (2);

	mono_jit_exec (domain, assembly, argc, argv);

	std::vector<MonoObject*> theObjs;
	create_object (domain, mono_assembly_get_image (assembly), &theObjs);

	while(1)
	for(int i =0; i < theObjs.size(); i++)
	{
		call_methods (theObjs.at(i), "Update");
	}
}

int 
main (int argc, char* argv[]) {
	MonoDomain *domain;
	const char *file;
	int retval;

	file = "AssemblyCSharp.dll"; //argv [1];

	domain = mono_jit_init (file);

	main_function (domain, file, argc - 1, argv + 1);

	retval = mono_environment_exitcode_get ();
	
	mono_jit_cleanup (domain);
	return retval;
}

