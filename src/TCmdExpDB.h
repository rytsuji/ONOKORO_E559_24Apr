/**
 * @file   TCmdPrint.h
 * @brief  print the last-saved figure
 *
 * @date   Created       : 2017-06-13 16:38:24 JST
 *         Last Modified : 2019-11-15 20:42:02 JST (ota)
 * @author KAWASE Shoichiro <kawase@aees.kyushu-u.ac.jp>
 *
 *    (C) 2017 KAWASE Shoichiro
 */

#ifndef INCLUDE_GUARD_UUID_9784A220_859C_4809_9B48_A9561F2CD114
#define INCLUDE_GUARD_UUID_9784A220_859C_4809_9B48_A9561F2CD114

#include "TCatCmd.h"

namespace art {
   class TCmdExpDB;
}

class art::TCmdExpDB : public TCatCmd {
public:
   TCmdExpDB();
   virtual ~TCmdExpDB();

   Long_t Run();
   Long_t Cmd(vector<TString>);
   void SetPrinter(const char* printer);
   void SetOption(const char* option);
   void SetCommand(const char* command) { fExpDB = command; }

protected:
   TString fFilePath; // printer name
   TString fExpDBCmd; // directly set the command
   

private:
   TCmdPrint(const TCmdPrint&); // undefined 
   TCmdPrint& operator=(const TCmdPrint&); // undefined

   ClassDef(TCmdPrint,0) // print the last-saved figure
};

#endif // INCLUDE_GUARD_UUID_9784A220_859C_4809_9B48_A9561F2CD114
