func = Module.cwrap('CalculateAllCandidateKeysWebWrapper', 'string', ['string','string']);
func('ABCDEF','DF->C,BC->F,E->A,ABC->E');


func = Module.cwrap('CalculateAttributeClosureWebWrapper', 'string', ['string','string']);
func('AG', 'A->B,A->C,CG->H,CI->G');

func = Module.cwrap('CalculateFDClosureWebWrapper', 'string', ['string','string']);
func('ABC', 'A->B,B->C');

func = Module.cwrap('CalculateMinimalCoverWebWrapper', 'string', ['string','string']);
func('ABC', 'A->BC,C->AB,B->AC');
