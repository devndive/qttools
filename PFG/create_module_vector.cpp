#include <boost/filesystem.hpp>
#include <iostream>
#include "create_module_vector.h"

namespace bfs = boost::filesystem;

namespace PFG
{

void createModuleVector( std::vector< stringList > &moduleVector, bool shortModules)
{
	std::string path("./modules/");
	bfs::path modulePath( path );

	if( bfs::exists( modulePath ) )
	{
		if ( bfs::is_directory( modulePath ) )
		{
			bfs::path initialPath = bfs::system_complete( bfs::path( path, bfs::native ) );
			bfs::directory_iterator endIter;

			for ( bfs::directory_iterator dirItr( modulePath ); dirItr != endIter; ++dirItr )
			{
				try
				{
					if ( bfs::is_regular( dirItr->status() ) )
					{
						std::string extension( bfs::extension( dirItr->leaf() ) );
						std::string basename( bfs::basename( dirItr->leaf() ) );
						std::string filename = dirItr->path().string().substr(dirItr->path().string().size() - basename.size() - extension.size(), dirItr->path().string().size() );

						if( shortModules )
						{
							if( filename.find("_short") != std::string::npos )
							{
								stringList includes;

								std::ifstream file( (initialPath / dirItr->leaf()).string().c_str() );
								includes.push_back( filename.substr( 0, filename.find( "_short" ) ) );
								
								while(file)
								{
									std::string line;
									std::getline(file, line);

									//includes.push_back(line);
									addToStringList(includes, line);
								}

								moduleVector.push_back( includes );
							}
						}
						else
						{
							if( filename.find("_short") == std::string::npos )
							{
								stringList includes;

								std::ifstream file( (initialPath / dirItr->leaf()).string().c_str() );
								includes.push_back( filename );

								while(file)
								{
									std::string line;
									std::getline(file, line);

									//includes.push_back(line);
									addToStringList(includes, line);
								}

								moduleVector.push_back( includes );
							}
						}
					}
				}
				catch ( const std::exception & ex )
				{
					std::cerr << dirItr->leaf() << " " << ex.what() << std::endl;
				}
			}
		}
	}
}

}