include TinyWonderEngine.Result;

let handleError = (handleFailFunc: 'f => unit, result: t('s, 'f)): unit =>
  switch (result) {
  | Success(s) => ()
  | Fail(f) => handleFailFunc(f)
  };