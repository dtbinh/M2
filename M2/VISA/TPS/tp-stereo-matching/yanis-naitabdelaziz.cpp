/* --------------------------------------------------------------------------
Mise en correspondance de points d'interet detectes dans deux images
Copyright (C) 2010, 2011  Universite Lille 1

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
-------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------
Inclure les fichiers d'entete
-------------------------------------------------------------------------- */
#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
#include "glue.hpp"
#include "yanis-naitabdelaziz.hpp"
#include <iostream>

// -----------------------------------------------------------------------
/// \brief Detecte les coins.
///
/// @param mImage: pointeur vers la structure image openCV
/// @param iMaxCorners: nombre maximum de coins detectes
/// @return matrice des coins
// -----------------------------------------------------------------------
Mat iviDetectCorners(const Mat& mImage,
                     int iMaxCorners){
    vector<Point2f> vCorners;


    goodFeaturesToTrack(mImage,vCorners,iMaxCorners,0.01,10,Mat(),3,false,0.04);
    Mat mCorners(3,vCorners.size(),CV_64F);
    for(int i=0;i<vCorners.size();i++){
        mCorners.at<double>(0,i)=(double)vCorners[i].x;
        mCorners.at<double>(1,i)=(double)vCorners[i].y;
        mCorners.at<double>(2,i)=1;
    }
    return mCorners;
}

// -----------------------------------------------------------------------
/// \brief Initialise une matrice de produit vectoriel.
///
/// @param v: vecteur colonne (3 coordonnees)
/// @return matrice de produit vectoriel
// -----------------------------------------------------------------------
Mat iviVectorProductMatrix(const Mat& v) {

    Mat mVectorProduct = Mat::eye(3, 3, CV_64F);

    mVectorProduct.at<double>(0,0) = (double)0.0;
    mVectorProduct.at<double>(0,1) = -v.at<double>(2,0);
    mVectorProduct.at<double>(0,2) = v.at<double>(1,0);

    mVectorProduct.at<double>(1,0) = v.at<double>(2,0);
    mVectorProduct.at<double>(1,1) = (double)0.0;
    mVectorProduct.at<double>(1,2) = -v.at<double>(0,0);

    mVectorProduct.at<double>(2,0) = -v.at<double>(1,0);
    mVectorProduct.at<double>(2,1) = v.at<double>(0,0);
    mVectorProduct.at<double>(2,2) = (double)0.0;

    return mVectorProduct;
}

// -----------------------------------------------------------------------
/// \brief Initialise et calcule la matrice fondamentale.
///
/// @param mLeftIntrinsic: matrice intrinseque de la camera gauche
/// @param mLeftExtrinsic: matrice extrinseque de la camera gauche
/// @param mRightIntrinsic: matrice intrinseque de la camera droite
/// @param mRightExtrinsic: matrice extrinseque de la camera droite
/// @return matrice fondamentale
// -----------------------------------------------------------------------
Mat iviFundamentalMatrix(const Mat& mLeftIntrinsic,
                         const Mat& mLeftExtrinsic,
                         const Mat& mRightIntrinsic,
                         const Mat& mRightExtrinsic) {
    // Doit utiliser la fonction iviVectorProductMatrix
    Mat mFundamental = Mat::eye(3, 3, CV_64F);

    Mat pLeft = mLeftIntrinsic * Mat::eye(3, 4, CV_64F) * mLeftExtrinsic;
    Mat pRight = mRightIntrinsic * Mat::eye(3, 4, CV_64F) * mRightExtrinsic;

    Mat o1 = mLeftExtrinsic.inv().col(3);
    Mat a = pRight*o1;
    Mat b = pRight*pLeft.inv(DECOMP_SVD);

    mFundamental = iviVectorProductMatrix(a)*b;

     Mat epiDroite,epiGauche,point;
     point = (Mat_<double>(3,1) << 640/2,480/2,1);
     epiDroite = mFundamental*point;
     epiGauche = mFundamental.t()*point;

     std::cout << "a = "<< epiDroite.at<double>(0,0)<< " b = "<< epiDroite.at<double>(1,0)<< " c = "<< epiDroite.at<double>(2,0)<<std::endl;
     std::cout << "a = "<< epiGauche.at<double>(0,0)<< " b = "<< epiGauche.at<double>(1,0)<< " c = "<< epiGauche.at<double>(2,0)<<std::endl;

    return mFundamental;
}

// -----------------------------------------------------------------------
/// \brief Initialise et calcule la matrice des distances entres les
/// points de paires candidates a la correspondance.
///
/// @param mLeftCorners: liste des points 2D image gauche
/// @param mRightCorners: liste des points 2D image droite
/// @param mFundamental: matrice fondamentale
/// @return matrice des distances entre points des paires
// -----------------------------------------------------------------------
Mat iviDistancesMatrix(const Mat& m2DLeftCorners,
                       const Mat& m2DRightCorners,
                       const Mat& mFundamental){
    double x1,y1,z1,x2,y2,z2,d1,d2;
    Mat epiDroite,epiGauche,point1,point2;
    int widthL,widthR;

    widthL = m2DLeftCorners.size().width;
    widthR = m2DRightCorners.size().width;

    Mat mDistances(widthL,widthR,CV_64F);

    for(int i=0;i<widthL;i++){

          x1 = m2DLeftCorners.at<double>(0,i);
          y1 = m2DLeftCorners.at<double>(1,i);
          z1 = m2DLeftCorners.at<double>(2,i);

          point1 = (Mat_<double>(3,1) << x1,y1,z1);

          epiDroite = mFundamental*point1;

          for(int j=0;j<widthR;j++){

               x2 = m2DRightCorners.at<double>(0,j);
               y2 = m2DRightCorners.at<double>(1,j);
               z2 = m2DRightCorners.at<double>(2,j);

               point2 = (Mat_<double>(3,1) << x2,y2,z2);
               epiGauche = mFundamental.t()*point2;

               d1 = abs(epiDroite.at<double>(0,0)*x2+epiDroite.at<double>(1,0)*y2+epiDroite.at<double>(2,0))/
                    (sqrt(epiDroite.at<double>(0,0)*epiDroite.at<double>(0,0)+epiDroite.at<double>(1,0)*epiDroite.at<double>(1,0)));

               d2 = abs(epiGauche.at<double>(0,0)*x1+epiGauche.at<double>(1,0)*y1+epiGauche.at<double>(2,0))/
                    (sqrt(epiGauche.at<double>(0,0)*epiGauche.at<double>(0,0)+epiGauche.at<double>(1,0)*epiGauche.at<double>(1,0)));

               mDistances.at<double>(i,j)=d1+d2;
          }
    }
    return mDistances;
}

// -----------------------------------------------------------------------
/// \brief Initialise et calcule les indices des points homologues.
///
/// @param mDistances: matrice des distances
/// @param fMaxDistance: distance maximale autorisant une association
/// @param mRightHomologous: liste des correspondants des points gauche
/// @param mLeftHomologous: liste des correspondants des points droite
/// @return rien
// -----------------------------------------------------------------------
void iviMarkAssociations(const Mat& mDistances,
                         double dMaxDistance,
                         Mat& mRightHomologous,
                         Mat& mLeftHomologous) {

     int continu = 0;

     int widthR =  mDistances.size().width;
     int widthL =  mDistances.size().height;

     mRightHomologous =  Mat::eye(1,widthR,CV_64F);
     mLeftHomologous = Mat::eye(1,widthL,CV_64F);

     for(int i=0;i<widthR;i++){
          mRightHomologous.at<int>(0,i)=-1;
     }

     for(int j=0;j<widthL;j++){
          mLeftHomologous.at<int>(0,j)=-1;
     }

     double dMin ;
     int indexLeftMin,indexRightMin;
     for(int i=0;i<widthL;i++){
          dMin = mDistances.at<double>(i,0);
          indexRightMin = -1;
          for(int j=0;j<widthR;j++){
               if(mDistances.at<double>(i,j)<=dMaxDistance){
                    if(mDistances.at<double>(i,j)<=dMin){
                         indexRightMin = j;
                         dMin = mDistances.at<double>(i,j);

                    }

               }
          }
          mLeftHomologous.at<int>(0,i) = indexRightMin;
     }

     for(int j=0;j<widthR;j++){
          dMin = mDistances.at<double>(0,j);
          indexLeftMin = -1;
          for(int i=0;i<widthL;i++){
               if(mDistances.at<double>(i,j)<=dMaxDistance){
                    if(mDistances.at<double>(i,j)<dMin){
                         indexLeftMin = i;
                         dMin = mDistances.at<double>(i,j);
                    }

               }
          }
          mRightHomologous.at<int>(0,j) = indexLeftMin;
     }
     int a=0;
     int b=0;
     for(int i=0;i<widthR;i++){
          std::cout << mRightHomologous.at<int>(0,i) << " | ";
          if(mRightHomologous.at<int>(0,i)==-1)
            a++;
     }
     std::cout << "------------------------------"<<std::endl;

     int nbHomologues = 0;

     for(int j=0;j<widthL;j++){
          std::cout << mLeftHomologous.at<int>(0,j) << " | ";
          if(mRightHomologous.at<int>(0,mLeftHomologous.at<int>(0,j))==j)
               nbHomologues++;
          if(mLeftHomologous.at<int>(0,j)==-1)
            b++;
     }


     std::cout << std::endl;

     std::cout << "Seuil = "<< dMaxDistance<<std::endl;
     std::cout << "Nombre de points homolgues = "<< nbHomologues<<std::endl;
     std::cout << "Nombre de points occultés droite = "<< a<<std::endl;
     std::cout << "Nombre de points occultés gauche = "<< b<<std::endl;




}
