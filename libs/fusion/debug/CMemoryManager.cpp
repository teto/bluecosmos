#if 0
#include


namespace fus {

//Recupere l'instance



void*
CMemoryManager::Allocate(std::size_t Size, const CFile& File,int Line,bool Array){
    // Allocation de la mémoire
    void* Ptr = malloc(Size);

    // Ajout du bloc à la liste des blocs alloués
    SBlock NewBlock = {Size,File,Line,Array};
    /*NewBlock.Size  = Size;
    NewBlock.File  = File;
    NewBlock.Line  = Line;
    NewBlock.Array = Array;*/
    m_Blocks[Ptr] = NewBlock;

    // Loggization
    m_File << "++ Allocation    | 0x" << Ptr
           << " | " << std::setw(7) << std::setfill(' ')
           << static_cast<int>(NewBlock.Size) << " octets"
           << " | " << NewBlock.File.FileName()
           << "(" << NewBlock.Line << ")" << std::endl;

    return Ptr;
}




void
CMemoryManager::Free(void* Ptr, bool Array){

    // Recherche de l'adresse dans les blocs alloués
    std::map<void*,SBlock>::iterator i = m_Blocks.find(Ptr);

    // Si le bloc n'a pas été alloué, on génère une erreur
    if (i == m_Blocks.end()){
        // En fait ça arrive souvent, du fait que le delete surchargé
        // est pris en compte même là où on n'inclue pas DebugNew.h,
        // mais pas la macro pour le new
        // Dans ce cas on détruit le bloc et on quitte immédiatement
        free(Ptr);
        return;
    }

    // Si le type d'allocation (tableau / objet) ne correspond pas, on génère une erreur
    if (i->second.Array != Array){
        //TODO !!
        //throw CBadDelete(Ptr, It->second.File.Filename(), It->second.Line, !Array);
        //std::cout << "error";
    }

    // Finalement, si tout va bien, on supprime le bloc et on loggiz tout ça
    m_File << "-- Désallocation | 0x" << Ptr
           << " | " << std::setw(7) << std::setfill(' ')
           << static_cast<int>(i->second.Size) << " octets"
           << " | " << m_DeleteStack.top().File.FileName()
           << " (" << m_DeleteStack.top().Line << ")" << std::endl;
    m_Blocks.erase(i);
    m_DeleteStack.pop();

    // Libération de la mémoire
    free(Ptr);
}



//Destructeur
CMemoryManager::~CMemoryManager(){

    // Aucune fuite
    if (m_Blocks.empty()){
        m_File << "     No leak detected !  " << std::endl;
    }
    // Fuites mémoires =(
    else{
        m_File << "WARNING: Some leaks have been detected ( " << m_Blocks.size() << " )" << std::endl;
        ReportLeaks();
    }
}


void CMemoryManager::ReportLeaks(){

    // Détail des fuites
    std::size_t TotalSize = 0;
    for (std::map<void*,SBlock>::iterator i = m_Blocks.begin(); i != m_Blocks.end(); ++i){

        // Ajout de la taille du bloc au cumul
        TotalSize += i->second.Size;

        // Inscription dans le fichier des informations sur le bloc courant
        m_File << "-> 0x" << i->first
               << " | "   << std::setw(7) << std::setfill(' ')
               << static_cast<int>(i->second.Size) << " octets"
               << " | "   << i->second.File.FileName()
               << " (" << i->second.Line << ")" << std::endl;

        // Libération de la mémoire
        free(i->first);
    }

    // Affichage du cumul des fuites
    m_File << std::endl << std::endl << "-- "
           << static_cast<int>(m_Blocks.size()) << " blocs non-libéré(s), "
           << static_cast<int>(TotalSize)       << " octets --"
           << std::endl;
}

//Prépare prochaine suppression
void CMemoryManager::NextDelete(const CFile& File, int Line){

    SBlock Delete;
    Delete.File = File;
    Delete.Line = Line;

    m_DeleteStack.push(Delete);
}

}
#endif
