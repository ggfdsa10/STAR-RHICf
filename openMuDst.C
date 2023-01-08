#include <string.h>
#include <iostream>

void openMuDst(){
    gSystem->Load("StRHICfUtil");
    gROOT->Macro("/star/u/slee5/rhicf_SL22b/StRoot/StMuDSTMaker/COMMON/macros/loadSharedLibraries.C");

    TStopwatch time_all;
    StMuDstMaker* mudst_mk=new StMuDstMaker(0,0,"","st_rhicf_18178002_raw_1000004.MuDst.root");
    mudst_mk->SetStatus("*",0);           
    mudst_mk->SetStatus("MuEvent",1);      
    mudst_mk->SetStatus("RHICf*",1); 
    mudst_mk->Init();

    // ================ ROOT file initialization for RHICf data ==================
    TFile* mTFile = new TFile("muDst_RHICf.root", "recreate");
    TTree* mRHICfTree = new TTree("RHICf", "RHICf");

    Int_t mRunNumber;
    Int_t mEventNumber;
    Int_t mBunchNumber;
    Int_t mRunType;
    Int_t mRHICfTrigger;
    Int_t mRunTime[2];
    Int_t mRunTRGM;

    unsigned int mTDC[256]; // TDC 
    unsigned int mCAD0[5];  // CAD0
    unsigned int mGPI0[19]; // GPI0
    unsigned int mGPI1[17]; // GPI1

    Int_t mPlateADC[2][16][2];
    Int_t mGSOBarADC[2][4][2][40];

    Int_t mParticleID[2];
    Int_t mGSOMaxLayer[2][2]; 
    Int_t mResultHitNum[2];
    Int_t mSingleHitNum[2][4][2];
    Int_t mMultiHitNum[2];
    Int_t mMaxPeakBin[2][4][2];

    Double_t mL20[2];
    Double_t mL90[2];
    Double_t mResultHitPos[2][2];
    Double_t mSingleHitPos[2][4][2];
    Double_t mMultiHitPos[2][4][2][2];
    Double_t mSinglePeakHeight[2][4][2];
    Double_t mMultiPeakHeight[2][4][2][2];
    Double_t mMultiPeakRaw[2][4][2][2];
    Double_t mMultiEnergySum[2][4][2][2];
    Double_t mSumEnergy[2][2];
    Double_t mResultEnergy[2][2];

    Double_t mSingleChiSquare[2][4][2];
    Double_t mMultiChiSquare[2][4][2];

    // StRHICfRawHit data part
    mRHICfTree -> Branch("RunNumber", &mRunNumber, "RunNumber/I");
    mRHICfTree -> Branch("EventNumber", &mEventNumber, "EventNumber/I");
    mRHICfTree -> Branch("BunchNumber", &mBunchNumber, "BunchNumber/I");
    mRHICfTree -> Branch("RunType", &mRunType, "RunType/I");
    mRHICfTree -> Branch("RHICfTrigger", &mRHICfTrigger, "RHICfTrigger/I");
    mRHICfTree -> Branch("RunTime", mRunTime, "RunTime[2]/I");
    mRHICfTree -> Branch("RunTRGM", &mRunTRGM, "RunTRGM/I");

    mRHICfTree -> Branch("mTDC", mTDC, "mTDC[256]/I");
    mRHICfTree -> Branch("mCAD0", mCAD0, "mCAD0[5]/I");
    mRHICfTree -> Branch("mGPI0", mGPI0, "mGPI0[19]/I");
    mRHICfTree -> Branch("mGPI1", mGPI1, "mGPI1[17]/I");

    // StRHICfHit and StRHICfPoint data part
    mRHICfTree -> Branch("PlateADC", mPlateADC, "mPlateADC[2][16][2]/I");
    mRHICfTree -> Branch("GSOBarADC", mGSOBarADC, "mGSOBarADC[2][4][2][40]/I");
    mRHICfTree -> Branch("GSOMaxLayer", mGSOMaxLayer, "mGSOMaxLayer[2][2]/I");
    mRHICfTree -> Branch("SingleHitNum", mSingleHitNum, "mSingleHitNum[2][4][2]/I");
    mRHICfTree -> Branch("MultiHitNum", mMultiHitNum, "mMultiHitNum[2]/I");
    mRHICfTree -> Branch("MaxPeakBin", mMaxPeakBin, "mMaxPeakBin[2][4][2]/I");

    mRHICfTree -> Branch("L20", mL20, "mL20[2]/D");
    mRHICfTree -> Branch("L90", mL90, "mL90[2]/D");

    mRHICfTree -> Branch("SingleHitPos", mSingleHitPos, "mSingleHitPos[2][4][2]/D");
    mRHICfTree -> Branch("MultiHitPos", mMultiHitPos, "mMultiHitPos[2][4][2][2]/D");
    mRHICfTree -> Branch("SinglePeakHeight", mSinglePeakHeight, "mSinglePeakHeight[2][4][2]/D");
    mRHICfTree -> Branch("MultiPeakHeight", mMultiPeakHeight, "mMultiPeakHeight[2][4][2][2]/D");
    mRHICfTree -> Branch("MultiPeakRaw", mMultiPeakRaw, "mMultiPeakRaw[2][4][2][2]/D");
    mRHICfTree -> Branch("MultiEnergySum", mMultiEnergySum, "mMultiEnergySum[2][4][2][2]/D");

    mRHICfTree -> Branch("SingleChiSquare", mSingleChiSquare, "mSingleChiSquare[2][4][2]/D");
    mRHICfTree -> Branch("MultiChiSquare", mMultiChiSquare, "mMultiChiSquare[2][4][2]/D");

    mRHICfTree -> Branch("PID", mParticleID, "mParticleID[2]/I");
    mRHICfTree -> Branch("ResultHitNum", mResultHitNum, "mResultHitNum[2]/I");
    mRHICfTree -> Branch("ResultHitPos", mResultHitPos, "mResultHitPos[2][2]/D");
    mRHICfTree -> Branch("mSumEnergy", mSumEnergy, "mSumEnergy[2][2]/D");
    mRHICfTree -> Branch("ResultEnergy", mResultEnergy, "ResultEnergy[2][2]/D");


    // ============ Init value for RHICf data ===============
    mRunNumber = 0;
    mEventNumber = 0;
    mBunchNumber = 0;
    mRunType = 0;
    mRHICfTrigger = 0;
    mRunTime[0] = 0;
    mRunTime[1] = 0;
    mRunTRGM = 0;

    memset(mTDC, 0, sizeof(mTDC));
    memset(mCAD0, 0, sizeof(mCAD0));
    memset(mGPI0, 0, sizeof(mGPI0));
    memset(mGPI1, 0, sizeof(mGPI1));

    memset(mPlateADC, -999, sizeof(mPlateADC));
    memset(mGSOBarADC, -999, sizeof(mGSOBarADC));

    memset(mParticleID, -999, sizeof(mParticleID));
    memset(mGSOMaxLayer, -999, sizeof(mGSOMaxLayer));
    memset(mResultHitNum, -999, sizeof(mResultHitNum));
    memset(mSingleHitNum, -999, sizeof(mSingleHitNum));
    memset(mMultiHitNum, -999, sizeof(mMultiHitNum));
    memset(mMaxPeakBin, -999, sizeof(mMaxPeakBin));

    memset(mL20, -999, sizeof(mL20));
    memset(mL90, -999, sizeof(mL90));
    memset(mResultHitPos, -999, sizeof(mResultHitPos));
    memset(mSingleHitPos, -999, sizeof(mSingleHitPos));
    memset(mMultiHitPos, -999, sizeof(mMultiHitPos));
    memset(mSinglePeakHeight, -999, sizeof(mSinglePeakHeight));
    memset(mMultiPeakHeight, -999, sizeof(mMultiPeakHeight));
    memset(mMultiPeakRaw, -999, sizeof(mMultiPeakRaw));
    memset(mMultiEnergySum, -999, sizeof(mMultiEnergySum));
    memset(mSumEnergy, -999, sizeof(mSumEnergy));
    memset(mResultEnergy, -999, sizeof(mResultEnergy));
    memset(mSingleChiSquare, -999, sizeof(mSingleChiSquare));
    memset(mMultiChiSquare, -999, sizeof(mMultiChiSquare));


    // ====================== read MuDst event ============================ 
    Int_t nEvent = mudst_mk->tree()->GetEntries();
    for (Int_t iEvent=0; iEvent<nEvent; iEvent++) {
        std::cout << "============ Working on event #[" << (iEvent+1) << "/" << nEvent << "] ==============" << std::endl;
        mudst_mk->Make();
        if (mudst_mk->muDst()==0) {
            cout << "No event" << endl;
            continue;
        }
        
        // access the MuDst 
        StMuDst *mudst=mudst_mk->muDst();
        // aceess the RHICf Collection
        StMuRHICfCollection* rhicfColl = mudst->muRHICfCollection();

        // RHICf Rawhit
        StMuRHICfRawHit* rawHitColl = rhicfColl->getRawHit();

		mBunchNumber = rawHitColl -> getBunchNumber();
		mRunType = rawHitColl -> getRunType();
		mRHICfTrigger = rawHitColl -> getTriggerNumber();
		mRunTime[0] = rawHitColl -> getRunTime(0);
		mRunTime[1] = rawHitColl -> getRunTime(1);
		mRunTRGM = rawHitColl -> getRunTRGM();

        for(int it=0; it<2; it++){
            for(int ip=0; ip<16; ip++){
                for(int io=0; io<2; io++){
                    mPlateADC[it][ip][io] = rawHitColl -> getPlateADC(it, ip, io);
                }
            }
            for(int il=0; il<4; il++){
                for(int ixy=0; ixy<2; ixy++){
                    int chSize = (it==0) ? 20 : 40;
                    for(int ich=0; ich<chSize; ich++){
                        mGSOBarADC[it][il][ixy][ich] = rawHitColl -> getGSOBarADC(it, il, ixy, ich);
                    }
                }
            }
        }

        for(int i=0; i<256; i++){
            if(i<5){mCAD0[i] = rawHitColl -> getCAD0(i);}
            if(i<19){mGPI0[i] = rawHitColl -> getGPI0(i);}
            if(i<17){mGPI1[i] = rawHitColl -> getGPI1(i);}
            mTDC[i] = rawHitColl -> getTDC(i);
        }

        // RHICf Hit 
        StMuRHICfHit* hitColl = rhicfColl->getHit();
        if(hitColl){
            for(int it=0; it<2; it++){
                mMultiHitNum[it] = hitColl -> getMultiHitNum(it);
                mL20[it] = hitColl -> getL20(it);
                mL90[it] = hitColl -> getL90(it);
                mGSOMaxLayer[it][0] = hitColl -> getGSOMaxLayer(it, 0);
                mGSOMaxLayer[it][1] = hitColl -> getGSOMaxLayer(it, 1);
                mResultHitNum[it] = hitColl -> getPointNum(it);

                for(int il=0; il<4; il++){
                    for(int ixy=0; ixy<2; ixy++){
                        mMaxPeakBin[it][il][ixy] = hitColl -> getMaxPeakBin(it, il, ixy);
                        mSingleHitNum[it][il][ixy] = hitColl -> getSingleHitNum(it, il, ixy);
                        mSingleHitPos[it][il][ixy] = hitColl -> getSingleHitPos(it, il, ixy);
                        mSinglePeakHeight[it][il][ixy] = hitColl -> getSinglePeakHeight(it, il, ixy);
                        mSingleChiSquare[it][il][ixy] = hitColl -> getSingleFitChi2(it, il, ixy);
                        mMultiChiSquare[it][il][ixy] = hitColl -> getMultiFitChi2(it, il, ixy);

                        for(int io=0; io<2; io++){
                            mMultiHitPos[it][il][ixy][io] = hitColl -> getMultiHitPos(it, il, ixy, io);
                            mMultiPeakHeight[it][il][ixy][io] = hitColl -> getMultiPeakHeight(it, il, ixy, io);
                            mMultiPeakRaw[it][il][ixy][io] = hitColl -> getMultiPeakRaw(it, il, ixy, io);
                            mMultiEnergySum[it][il][ixy][io] = hitColl -> getMultiEnergySum(it, il, ixy, io);
                        }
                    }
                }
            }

            // RHICf Point
            Int_t pointCollNum = rhicfColl->numberOfPoints();
            for(int classNum = 0; classNum<pointCollNum; classNum++){
                StMuRHICfPoint* pointColl = rhicfColl->getPoint(classNum);
                Int_t towerIdx = pointColl -> getTowerIdx();

                mParticleID[towerIdx] = pointColl -> getPID();
                mSumEnergy[towerIdx][0] = pointColl->getTowerSumEnergy(0);
                mSumEnergy[towerIdx][1] = pointColl->getTowerSumEnergy(1);
                mResultHitPos[towerIdx][0] = pointColl->getPointPos(0);
                mResultHitPos[towerIdx][1] = pointColl->getPointPos(1);
                mResultEnergy[towerIdx][0] = pointColl->getPointEnergy(0);
                mResultEnergy[towerIdx][1] = pointColl->getPointEnergy(1);

                cout << towerIdx << " " << mResultHitPos[towerIdx][0] << " " << mResultHitPos[towerIdx][1] << " | " << mResultEnergy[towerIdx][0] << " " << mResultEnergy[towerIdx][1] << endl;
            }
        }

        mRHICfTree -> Fill();
    }

    mTFile -> cd();
    mRHICfTree -> Write();
    mTFile -> Close();

    cout << "****************************************** " << endl;
	cout << "read MuDst Work done...                  " << endl;
	cout << "****************************************** " << endl;
	cout << "total number of events  " << nEvent << endl;
	cout << "****************************************** " << endl;
}
