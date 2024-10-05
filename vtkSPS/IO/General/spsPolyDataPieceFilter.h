/*=========================================================================

  Program:   Single Purpose Solutions
  Module:    spsPolyDataPieceFilter.h

  Copyright (c) Jens Munk Hansen
  All rights reserved.
  See Copyright.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/**
 * @class   spsPolyDataPieceFilter
 * @brief   Provide pieces for upstream filters
 *
 * PolyDataPieceFilter is a filter, which can subdivide vtkPolyData into pieces for spatial
 * streaming.
 *
 */

#ifndef spsPolyDataPieceFilter_h
#define spsPolyDataPieceFilter_h

#include "spsIOGeneralModule.h"
#include "vtkPolyDataAlgorithm.h"

class SPSIOGENERAL_EXPORT spsPolyDataPieceFilter : public vtkPolyDataAlgorithm
{
public:
  vtkTypeMacro(spsPolyDataPieceFilter, vtkPolyDataAlgorithm);
  void PrintSelf(std::ostream& os, vtkIndent indent) override;

  static spsPolyDataPieceFilter* New();

  /**
   * Upstream producer can handle piece requests
   */
  vtkGetMacro(PiecesHandledUpstream, vtkTypeBool);

protected:
  spsPolyDataPieceFilter();
  ~spsPolyDataPieceFilter() override;

  // RequestData is called for each piece and processes the data for the requested piece
  int RequestData(vtkInformation* request, vtkInformationVector** inputVector,
    vtkInformationVector* outputVector) override;
  // RequestUpdateExtent is called to define which part of the data we want to process
  int RequestUpdateExtent(vtkInformation* request, vtkInformationVector** inputVector,
    vtkInformationVector* outputVector) override;
  // RequestInformation is called to provide meta-information about the filter output
  int RequestInformation(vtkInformation* request, vtkInformationVector** inputVector,
    vtkInformationVector* outputVector) override;

  vtkTypeBool PiecesHandledUpstream;

private:
  spsPolyDataPieceFilter(const spsPolyDataPieceFilter&) = delete;
  void operator=(const spsPolyDataPieceFilter&) = delete;
};

#endif
