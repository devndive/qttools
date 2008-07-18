#include <boost/filesystem.hpp>
#include <iostream>

#include "get_all_files.h"

namespace bfs = boost::filesystem;

int get_all_files_rec(bfs::path&, bfs::path&, fileList&, fileList&, fileList&, fileList&, pathList&);
void addToPathList(pathList &list, std::string &toAdd);

void get_all_files(std::string &path, fileList &h_files, fileList &cpp_files, fileList &qrc_files, fileList &uic_files, pathList &depend_paths)
{
	bfs::path initial_path( bfs::initial_path<bfs::path>() );

	initial_path = bfs::system_complete( bfs::path( path, bfs::native ) );
	get_all_files_rec(initial_path, initial_path, h_files, cpp_files, qrc_files, uic_files, depend_paths);
}

int get_all_files_rec(bfs::path &full_path, bfs::path &initial_path, fileList &h_files, fileList &cpp_files, fileList &qrc_files, fileList &uic_files, pathList &depend_paths)
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
					get_all_files_rec(bfs::system_complete( bfs::path( dir_itr->path().string(), bfs::native ) ), initial_path, h_files, cpp_files, qrc_files, uic_files, depend_paths);
				}
				else if ( bfs::is_regular( dir_itr->status() ) )
				{
					std::string relative = dir_itr->path().string().substr(initial_path.string().size() + 1, dir_itr->path().string().size() );

					std::string extension( bfs::extension( dir_itr->leaf() ) );
					std::string basename( bfs::basename( dir_itr->leaf() ) );
					std::string filename = dir_itr->path().string().substr(dir_itr->path().string().size() - basename.size() - extension.size(), dir_itr->path().string().size() );

					std::string filepath = dir_itr->path().string().substr(initial_path.string().size() + 1, dir_itr->path().string().size() - initial_path.string().size() - 2 - filename.size() );
					
					if( extension == ".cpp" )
					{
						if( dir_itr->path().string().find( "moc_" ) == std::string::npos && dir_itr->path().string().find( "qrc_" ) == std::string::npos )
						{
							//std::cout << "relative: " << relative << std::endl;
							cpp_files.push_back( relative );
							//std::cout << "filepath: " << filepath << std::endl;

							if(filepath != filename)
							{
								addToPathList(depend_paths, filepath);
							}
						}
					}
					else if( extension == ".h" )
					{
						//if( dir_itr->path().string().find_first_of( initial_path.string() ) >= 0 )
						//{
						//std::cout << "relative: " << relative << std::endl;
						h_files.push_back( relative );
						//std::cout << "filepath: " << filepath << std::endl;
						if(filepath != filename)
						{
							addToPathList(depend_paths, filepath);
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
							addToPathList(depend_paths, filepath);
						}
						//}					
					}
					else if( extension == ".uic" )
					{
						uic_files.push_back( relative );
						if( filepath != filename)
						{
							addToPathList(depend_paths, filepath);
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

void addToPathList(pathList &l, std::string &toAdd)
{
	pathList::iterator result = std::find(l.begin(), l.end(), toAdd);

	if( result == l.end() )
	{
		l.push_back(toAdd);
	}
}
