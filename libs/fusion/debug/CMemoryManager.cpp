#if 0
#include


namespace fus {

//Recupere l'instance



void*
CMemoryManager::Allocate(std::size_t Size, const CFile& File,int Line,bool Array){
    // Allocation de la m�moire
    void* Ptr = malloc(Size);

    // Ajout du bloc � la liste des blocs allou�s
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

    // Recherche de l'adresse dans les blocs allou�s
    std::map<void*,SBlock>::iterator i = m_Blocks.find(Ptr);

    // Si le bloc n'a pas �t� allou�, on g�n�re une erreur
    if (i == m_Blocks.end()){
        // En fait �a arrive souvent, du fait que le delete surcharg�
        // est pris en compte m�me l� o� on n'inclue pas DebugNew.h,
        // mais pas la macro pour le new
        // Dans ce cas on d�truit le bloc et on quitte imm�diatement
        free(Ptr);
        return;
    }

    // Si le type d'allocation (tableau / objet) ne correspond pas, on g�n�re une erreur
    if (i->second.Array != Array){
        //TODO !!
        //throw CBadDelete(Ptr, It->second.File.Filename(), It->second.Line, !Array);
        //std::cout << "error";
    }

    // Finalement, si tout va bien, on supprime le bloc et on loggiz tout �a
    m_File << "-- D�sallocation | 0x" << Ptr
           << " | " << std::setw(7) << std::setfill(' ')
           << static_cast<int>(i->second.Size) << " octets"
           << " | " << m_DeleteStack.top().File.FileName()
           << " (" << m_DeleteStack.top().Line << ")" << std::endl;
    m_Blocks.erase(i);
    m_DeleteStack.pop();

    // Lib�ration de la m�moire
    free(Ptr);
}



//Destructeur
CMemoryManager::~CMemoryManager(){

    // Aucune fuite
    if (m_Blocks.empty()){
        m_File << "     No leak detected !  " << std::endl;
    }
    // Fuites m�moires =(
    else{
        m_File << "WARNING: Some leaks have been detected ( " << m_Blocks.size() << " )" << std::endl;
        ReportLeaks();
    }
}


void CMemoryManager::ReportLeaks(){

    // D�tail des fuites
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

        // Lib�ration de la m�moire
        free(i->first);
    }

    // Affichage du cumul des fuites
    m_File << std::endl << std::endl << "-- "
           << static_cast<int>(m_Blocks.size()) << " blocs non-lib�r�(s), "
           << static_cast<int>(TotalSize)       << " octets --"
           << std::endl;
}

//Pr�pare prochaine suppression
void CMemoryManager::NextDelete(const CFile& File, int Line){

    SBlock Delete;
    Delete.File = File;
    Delete.Line = Line;

    m_DeleteStack.push(Delete);
}

}
#endif
