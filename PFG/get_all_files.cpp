#include <boost/filesystem.hpp>
#include <iostream>

#include "get_all_files.h"

namespace bfs = boost::filesystem;

namespace PFG
{

int getAllFilesRec(const bfs::path&, bfs::path&, stringList&, stringList&, stringList&, stringList&, stringList&);
//void addToPathList(pathList &list, const std::string &toAdd);

void getAllFiles(const std::string &path, stringList &hFiles, stringList &cppFiles, stringList &qrcFiles, stringList &uicFiles, stringList &dependPaths)
{
	bfs::path initialPath( bfs::initial_path<bfs::path>() );

	if( path[path.size() - 1] == '/' )
	{
		initialPath = bfs::system_complete( bfs::path( path.substr(0, path.size() - 1), bfs::native ) );
	}
	else
	{
		initialPath = bfs::system_complete( bfs::path( path, bfs::native ) );
	}

	getAllFilesRec(initialPath, initialPath, hFiles, cppFiles, qrcFiles, uicFiles, dependPaths);
}

int getAllFilesRec(const bfs::path &full_path, bfs::path &initial_path, stringList &h_files, stringList &cpp_files, stringList &qrc_files, stringList &uic_files, stringList &depend_paths)
{
	if ( !bfs::exists( full_path ) )
	{
		std::cout << "\nNot found: " << full_path.native_file_string() << std::endl;
		return 1;
	}

	if ( bfs::is_directory( full_path ) )
	{
		bfs::directory_iterator end_iter;

		for ( bfs::directory_iterator dir_itr( full_path ); dir_itr != end_iter; ++dir_itr )
		{
			try
			{
				if ( bfs::is_directory( dir_itr->status() ) )
				{
					getAllFilesRec(bfs::system_complete( bfs::path( dir_itr->path().string(), bfs::native ) ), initial_path, h_files, cpp_files, qrc_files, uic_files, depend_paths);
				}
				else if ( bfs::is_regular( dir_itr->status() ) )
				{
					std::string relative = dir_itr->path().string().substr(initial_path.string().size() + 1, dir_itr->path().string().size() );

					std::string extension( bfs::extension( dir_itr->leaf() ) );
					std::string basename( bfs::basename( dir_itr->leaf() ) );
					std::string filename = dir_itr->path().string().substr(dir_itr->path().string().size() - basename.size() - extension.size(), dir_itr->path().string().size() );

					std::string filepath = dir_itr->path().string().substr(initial_path.string().size() + 1, dir_itr->path().string().size() - initial_path.string().size() - 2 - filename.size() );
					
					if( extension == ".cpp" || extension == ".cc" )
					{
						if( dir_itr->path().string().find( "moc_" ) == std::string::npos && dir_itr->path().string().find( "qrc_" ) == std::string::npos )
						{
							//std::cout << "relative: " << relative << std::endl;
							cpp_files.push_back( relative );
							//std::cout << "filepath: " << filepath << std::endl;

							if(filepath != filename)
							{
								addToStringList(depend_paths, filepath);
							}
						}
					}
					else if( extension == ".h" || extension == ".hpp" )
					{
						//if( dir_itr->path().string().find_first_of( initial_path.string() ) >= 0 )
						//{
						//std::cout << "relative: " << relative << std::endl;
						h_files.push_back( relative );
						//std::cout << "filepath: " << filepath << std::endl;
						if(filepath != filename)
						{
							addToStringList(depend_paths, filepath);
						}
						//}
					}
					else if( extension == ".qrc" || extension == ".rc" )
					{
						//if( dir_itr->path().string().find_first_of( initial_path.string() ) >= 0 )
						//{
						//std::cout << "relative: " << relative << std::endl;
						qrc_files.push_back( relative );
						//std::cout << "filepath: " << filepath << std::endl;
						if(filepath != filename)
						{
							addToStringList(depend_paths, filepath);
						}
						//}					
					}
					else if( extension == ".uic" || extension == ".ui" )
					{
						uic_files.push_back( relative );
						if( filepath != filename)
						{
							addToStringList(depend_paths, filepath);
						}
					}
				}
				/*else
				{
					std::cout << dir_itr->leaf() << " [other]\n";
				}*/
			}
			catch ( const std::exception & ex )
			{
				std::cerr << dir_itr->leaf() << " " << ex.what() << std::endl;
			}
		}
	}
	else
	{
		std::cerr << "\nFound: " << full_path.native_file_string() << "\n";    
	}

	return(0);
}
/*
void addToPathList(pathList &l, const std::string &toAdd)
{
	pathList::iterator result = std::find(l.begin(), l.end(), toAdd);

	if( result == l.end() )
	{
		l.push_back(toAdd);
	}
}
*/
} // namespace PFG

