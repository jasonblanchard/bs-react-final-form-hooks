let stringifyField = (fieldProps: Hooks.fieldRenderProps) => {
  let inputJs = Hooks.fieldInputRenderPropsToJs(fieldProps.input);
  let metaJs = Hooks.fieldMetaRenderPropsToJs(fieldProps.meta);
  let fieldJs = {"input": inputJs, "meta": metaJs};
  let stringified = Js.Json.stringifyAny(fieldJs);

  switch (stringified) {
  | Some(string) => string
  | None => ""
  };
};

let stringifyForm = (formProps: Hooks.formRenderProps) => {
  let formJs = Hooks.formRenderPropsToJs(formProps);

  let stringified = Js.Json.stringifyAny(formJs);

  switch (stringified) {
  | Some(string) => string
  | None => ""
  };
};
