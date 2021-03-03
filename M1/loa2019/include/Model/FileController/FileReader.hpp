#ifndef INCLUDE_MODEL_FILECONTROLLER_FILEREADER_HPP_
#define INCLUDE_MODEL_FILECONTROLLER_FILEREADER_HPP_

#include <stdexcept>


#include "FileController.hpp"
#include "Model/Board/Board.hpp"
#include "Model/Level.hpp"
#include "Model/GameObject/Monster/Monster.hpp"
#include "Model/GameObject/Moveable.hpp"
#include "Model/GameObject/Player.hpp"
#include "Model/GameObject/Charger.hpp"
#include "Util/Point2D.hpp"
#include "Model/Links.hpp"
#include "Model/Game.hpp"
#include "Model/AI/AI.hpp"
#include "Model/AI/DefaultAI.hpp"
#include "Model/Color.hpp"

class FileReader : public virtual FileController{

    public :
        FileReader();
        ~FileReader();
        Game * readGame(std::string const &path);


    private :

};
#endif // INCLUDE_MODEL_FILECONTROLLER_FILEREADER_HPP_
