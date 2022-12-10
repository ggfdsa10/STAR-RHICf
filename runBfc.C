TString opt = "in Event l0 trgd ZDCvtx EvOut CMuDst eemcDb emcDY2 rhicfdat pp2pp tpcDb"; // rhicfdat : rhicf raw data save option

void runBfc(const Char_t *file="/star/data03/daq/2017/178/18178002/st_rhicf_18178002_raw_1000004.daq", Int_t nevents=100){ 
	gROOT->LoadMacro("bfc.C");  // Load big "full" chain
	bfc(-1,opt,file);     // Setup but do not init

	// Intializet the chain
	chain->Init();

	// Process events
	chain->EventLoop(nevents);    
}
