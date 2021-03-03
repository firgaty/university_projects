#ifndef INCLUDE_MODEL_FILECONTROLLER_FILEWRITER_HPP_
#define INCLUDE_MODEL_FILECONTROLLER_FILEWRITER_HPP_

#include "Model/FileController/FileController.hpp"
#include "Model/Level.hpp"
#include "Model/Color.hpp"
#include "Model/AI/AI.hpp"
#include "Model/AI/DefaultAI.hpp"
#include "Model/Color.hpp"
#include "Model/GameObject/Monster/Monster.hpp"
#include "Model/GameObject/Moveable.hpp"
#include "Model/GameObject/Player.hpp"
#include "Model/GameObject/Charger.hpp"
#include "Util/Point2D.hpp"
#include "Model/Links.hpp"

class FileWriter : public virtual FileController{

    public :
        FileWriter();
        ~FileWriter();
        bool writeBoardFile(Game * game, std::string const path);
    private :

};
#endif // INCLUDE_MODEL_FILECONTROLLER_FILEWRITER_HPP_
