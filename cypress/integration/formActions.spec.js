it('works', () => {
  cy.visit  ('/actions');
  cy.get("input[name='firstName']").type('Gob');
  cy.get("input[name='lastName']").type('Bluth');

  cy.contains('Gob');
  cy.contains('Bluth');
  cy.contains("reset").click();
  cy.contains('Gob').should('not.exist');;
  cy.contains('Bluth').should('not.exist');;
});